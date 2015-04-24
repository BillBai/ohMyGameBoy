#include "GBCPU.h"

namespace GameBoy
{
	GBCPU::GBCPU()
	{
	}

	GBCPU::~GBCPU()
	{
	}

	// nothing to do
	void GBCPU::NOP()
	{
	}

	void GBCPU::LD_BC_nn()
	{
		regC = memoryUnit->readByte(regSP);
		regB = memoryUnit->readByte(regSP + 1);
		regPC += 2;
	}

	void GBCPU::LD_mBC_A()
	{
		word addr = combineByteToWord(regB, regC);
		memoryUnit->writeByte(addr, regA);
	}

	void GBCPU::INC_BC()
	{
		word BC = combineByteToWord(regB, regC) + 1;
		regB = getHighByte(BC);
		regC = getLowByte(BC);
	}

	void GBCPU::INC_B()
	{
		regB += 1;

		if (regB == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regB & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();
	}

	void GBCPU::DEC_B()
	{
		regB -= 1;

		if (regB == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regB & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void GBCPU::LD_B_n()
	{
		regB = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void GBCPU::RLCA()
	{
		// if regA[7] is 1
		if (regA > 0x7F) {
			setCarryFlag();
		} else {
			clearCarryFlag();
		}

		regA = (regA << 1) | (regA >> 7);

		clearZeroFlag();
		clearHalfCarryFlag();
		clearSubtractFlag();
	}

	void GBCPU::LD_mnn_SP()
	{
		address addr = memoryUnit->readWord(regPC);
		memoryUnit->writeWord(addr, regSP);
		regPC += 2;
	}

	void GBCPU::ADD_HL_BC()
	{
		word HL = combineByteToWord(regH, regL);
		word BC = combineByteToWord(regB, regC);
		word sum = HL + BC;

		if ((HL & 0x0FFF) > (sum & 0x0FFF)) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		regH = getHighByte(sum);
		regL = getLowByte(sum);

		clearSubtractFlag();

		if (sum < HL || sum < BC) {
			setCarryFlag();
		} else {
			clearCarryFlag();
		}
	}

	void GBCPU::LD_A_mBC()
	{
		regA = memoryUnit->readByte(combineByteToWord(regB, regC));
	}

	void GBCPU::DEC_BC()
	{
		word tmp = combineByteToWord(regB, regC) - 1;
		regB = getHighByte(tmp);
		regC = getLowByte(tmp);
	}

	void GBCPU::INC_C()
	{
		regC += 1;

		if (regC == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regC & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();
	}

	void GBCPU::DEC_C()
	{
		regC -= 1;

		if (regC == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regC & 0x0F) == 0x0F) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void GBCPU::LD_C_n()
	{
		regC = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void GBCPU::RRCA()
	{
		regA = (regA >> 1) | (regA << 7);

		if (regA > 0x7F) {
			setCarryFlag();
		} else {
			clearCarryFlag();
		}

		clearZeroFlag();
		clearSubtractFlag();
		clearHalfCarryFlag();
	}

	// 0x10 ~ 0x1F
	void GBCPU::STOP()
	{
		// TODO: handle stop
	}

	void GBCPU::LD_DE_nn()
	{
		regD = memoryUnit->readByte(regPC);
		regE = memoryUnit->readByte(regPC + 1);
		regPC += 2;
	}

	void GBCPU::LD_mDE_A()
	{
		address addr = combineByteToWord(regD, regE);
		memoryUnit->writeWord(addr, regA);
	}

	void GBCPU::INC_DE()
	{
		word tmp = combineByteToWord(regD, regE) + 1;
		regD = getHighByte(tmp);
		regE = getLowByte(tmp);
	}

	void GBCPU::INC_D()
	{
		regD += 1;
		if (regD == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regD & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();
	}

	void GBCPU::DEC_D()
	{
		regD -= 1;
		if (regD == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regD & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void GBCPU::LD_D_n()
	{
		regD = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void GBCPU::RLA()
	{
		byte carryFlag = getCarryFlag() ? 0x1 : 0x0;
		if (regA > 0x7F) {
			setCarryFlag();
		} else {
			clearCarryFlag();
		}

		regA = regA << 1 | carryFlag;

		clearZeroFlag();
		clearHalfCarryFlag();
		clearSubtractFlag();
	}

	void GBCPU::JR_n()
	{
		word offset = static_cast<word>(memoryUnit->readByte(regPC));
		regPC = regPC + offset;
	}

	void GBCPU::ADD_HL_DE()
	{
		word HL = combineByteToWord(regH, regL);
		word DE = combineByteToWord(regD, regE);
		word sum = HL + DE;

		if ((HL & 0x0FFF) > (sum & 0x0FFF)) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		regH = getHighByte(sum);
		regL = getLowByte(sum);

		if (sum < HL || sum < DE) {
			setCarryFlag();
		} else {
			clearCarryFlag();
		}

		clearSubtractFlag();
	}

	void GBCPU::LD_A_mDE()
	{
		regA = memoryUnit->readByte(combineByteToWord(regD, regE));
	}

	void GBCPU::DEC_DE()
	{
		word DE = combineByteToWord(regD, regE) - 1;
		regD = getHighByte(DE);
		regE = getLowByte(DE);
	}

	void GBCPU::INC_E()
	{
		regE += 1;

		if (regE == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regE & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();
	}

	void GBCPU::DEC_E()
	{
		regE -= 1;
		if (regE == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regE & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void GBCPU::LD_E_n()
	{
		regE = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void GBCPU::RRA()
	{
		byte carryFlag = getCarryFlag() ? 0x1 : 0x0;

		if ((regA & 0x01) == 1) {
			setCarryFlag();
		} else {
			clearCarryFlag();
		}
		regA = regA >> 1 | carryFlag;

		clearHalfCarryFlag();
		clearSubtractFlag();
		clearHalfCarryFlag();
	}

	// 0x20 ~ 0x2F
	void GBCPU::JR_NZ_n()
	{
		if (!getZeroFlag()) {
			regPC = regPC + memoryUnit->readByte(regPC);
		} else {
			regPC += 1;
		}
	}

	void GBCPU::LD_HL_nn()
	{
		regH = memoryUnit->readByte(regPC + 1);
		regL = memoryUnit->readByte(regPC);
		regPC += 2;
	}

	void GBCPU::LDI_mHL_A()
	{
		memoryUnit->writeWord(combineByteToWord(regH, regL), regA);
		word HL = combineByteToWord(regH, regL) + 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void GBCPU::INC_HL()
	{
		word HL = combineByteToWord(regH, regL) + 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void GBCPU::INC_H()
	{
		regH += 1;
		
		if (regH == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regH & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();
	}
	
	void GBCPU::DEC_H()
	{
		regH -= 1;
		
		if (regH == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regH & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void GBCPU::LD_H_n()
	{
		regH = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void GBCPU::DAA()
	{
		// TODO:
	}

	void GBCPU::JR_Z_n()
	{
		if (getZeroFlag()) {
			regPC = regPC + memoryUnit->readByte(regPC);
		} else {
			regPC += 1;
		}
	}

	void GBCPU::ADD_HL_HL()
	{
		word HL = combineByteToWord(regH, regL);
		if ((HL & 0x0FFF) > 0x07FF) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		// HL + HL == HL * 2
		byte sum = HL << 1;
		regH = getHighByte(sum);
		regL = getLowByte(sum);
	}

	void GBCPU::LDI_A_mHL()
	{
		regA = memoryUnit->readByte(combineByteToWord(regH, regL));
		word HL = combineByteToWord(regH, regL) + 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void GBCPU::DEC_HL()
	{
		word HL = combineByteToWord(regH, regL) - 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void GBCPU::INC_L()
	{
		regL += 1;
		if (regL == 0) { 
			setZeroFlag(); 
		} else {
			clearZeroFlag();
		}

		if ((regL & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();
	}

	void GBCPU::DEC_L()
	{
		regL -= 1;
		if (regL == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regL & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void GBCPU::LD_L_n()
	{
		regL = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void GBCPU::CPL()
	{
		regA ^= 0xFF;
		setSubtractFlag();
		setHalfCarryFlag();
	}

	// 0x30 ~ 0x3F
	void GBCPU::JR_NC_n()
	{
		if (!getCarryFlag()) {
			regPC = regPC + memoryUnit->readByte(regPC);
		} else {
			regPC += 1;
		}
	}

	void GBCPU::LD_SP_nn()
	{
		byte high = memoryUnit->readByte(regPC + 1);
		byte low = memoryUnit->readByte(regPC);
		regSP = combineByteToWord(high, low);
	}

	void GBCPU::LDD_mHL_A()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regA);
		HL -= 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void GBCPU::INC_SP()
	{
		regSP += 1;
	}

	void GBCPU::INC_mHL()
	{
		word addr = combineByteToWord(regH, regL);
		byte tmp = memoryUnit->readByte(addr) + 1;
		
		if (tmp == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((tmp & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}
		
		clearSubtractFlag();

		memoryUnit->writeByte(addr, tmp);
	}

	void GBCPU::DEC_mHL()
	{
		word addr = combineByteToWord(regH, regL);
		byte tmp = memoryUnit->readByte(addr) - 1;

		if (tmp == 0) {
			setZeroFlag();
		}
		else {
			clearZeroFlag();
		}

		if ((tmp & 0x0F) == 0x0F) {
			setHalfCarryFlag();
		}
		else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();

		memoryUnit->writeByte(addr, tmp);
	}

	void GBCPU::LD_mHL_n()
	{
		byte val = memoryUnit->readByte(regPC);
		word addr = combineByteToWord(regH, regL);
		memoryUnit->writeByte(addr, val);
		regPC += 1;
	}

	void GBCPU::SCF()
	{
		setCarryFlag();
		clearHalfCarryFlag();
		clearSubtractFlag();
	}

	void GBCPU::JR_C_n()
	{
		if (getCarryFlag()) {
			regPC = regPC + memoryUnit->readByte(regPC);
		} else {
			regPC += 1;
		}
	}

	void GBCPU::ADD_HL_SP()
	{
		word HL = combineByteToWord(regH, regL);
		word sum = HL + regSP;
		
		if ((HL & 0x0FFF) > (sum & 0xFFF)) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();

		if ((sum < HL) || (sum < regSP)) {
			setCarryFlag();
		} else {
			clearCarryFlag();
		}

		regH = getHighByte(sum);
		regL = getLowByte(sum);
	}

	void GBCPU::LDD_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regA = memoryUnit->readByte(HL);
		HL -= 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void GBCPU::DEC_SP()
	{
		regSP -= 1;
	}

	void GBCPU::INC_A()
	{
		regA += 1;
		if (regA == 0) {
			setZeroFlag();
		} else {
			clearZeroFlag();
		}

		if ((regA & 0x0F) == 0) {
			setHalfCarryFlag();
		} else {
			clearHalfCarryFlag();
		}

		clearSubtractFlag();
	}

	void GBCPU::DEC_A()
	{
		regA -= 1;
		if (regA == 0) {
			setZeroFlag();
		}
		else {
			clearZeroFlag();
		}

		if ((regA & 0x0F) == 0x0F) {
			setHalfCarryFlag();
		}
		else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void GBCPU::LD_A_n()
	{
		regA = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void GBCPU::CCF()
	{
		if (getCarryFlag) {
			clearCarryFlag();
		} else {
			setCarryFlag();
		}

		clearHalfCarryFlag();
		clearSubtractFlag();
	}

	// 0x40 ~ 0x4F
	void GBCPU::LD_B_B()
	{
		// Nothing to be done
	}

	void GBCPU::LD_B_C()
	{
		regB = regC;
	}

	void GBCPU::LD_B_D()
	{
		regB = regD;
	}

	void GBCPU::LD_B_E()
	{
		regB = regE;
	}

	void GBCPU::LD_B_H()
	{
		regB = regH;
	}

	void GBCPU::LD_B_L()
	{
		regB = regL;
	}

	void GBCPU::LD_B_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regB = memoryUnit->readByte(HL);
	}

	void GBCPU::LD_B_A()
	{
		regB = regA;
	}

	void GBCPU::LD_C_B()
	{
		regC = regB;
	}

	void GBCPU::LD_C_C()
	{
		// Nothing to be done
	}

	void GBCPU::LD_C_D()
	{
		regC = regD;
	}

	void GBCPU::LD_C_E()
	{
		regC = regE;
	}

	void GBCPU::LD_C_H()
	{
		regC = regH;
	}

	void GBCPU::LD_C_L()
	{
		regC = regL;
	}

	void GBCPU::LD_C_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regC = memoryUnit->readByte(HL);
	}

	void GBCPU::LD_C_A()
	{
		regC = regA;
	}

	// 0x50 ~ 0x5F
	void GBCPU::LD_D_B()
	{
		regD = regB;
	}

	void GBCPU::LD_D_C()
	{
		regD = regC;
	}

	void GBCPU::LD_D_D()
	{
		// nothing to be done
	}

	void GBCPU::LD_D_E()
	{
		regD = regE;
	}

	void GBCPU::LD_D_H()
	{
		regD = regH;
	}

	void GBCPU::LD_D_L()
	{
		regD = regL;
	}

	void GBCPU::LD_D_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regD = memoryUnit->readByte(HL);
	}

	void GBCPU::LD_D_A()
	{
		regD = regA;
	}

	void GBCPU::LD_E_B()
	{
		regE = regB;
	}

	void GBCPU::LD_E_C()
	{
		regE = regC;
	}

	void GBCPU::LD_E_D()
	{
		regE = regD;
	}

	void GBCPU::LD_E_E()
	{
		// nothing to do
	}

	void GBCPU::LD_E_H()
	{
		regE = regH;
	}

	void GBCPU::LD_E_L()
	{
		regE = regL;
	}

	void GBCPU::LD_E_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regE = memoryUnit->readByte(HL);
	}

	void GBCPU::LD_E_A()
	{
		regE = regA;
	}

	// 0x60 ~ 0x6F
	void GBCPU::LD_H_B()
	{
		regH = regB;
	}

	void GBCPU::LD_H_C()
	{
		regH = regC;
	}

	void GBCPU::LD_H_D()
	{
		regH = regD;
	}

	void GBCPU::LD_H_E()
	{
		regH = regE;
	}

	void GBCPU::LD_H_H()
	{
		// nothing to do
	}

	void GBCPU::LD_H_L()
	{
		regH = regL;
	}

	void GBCPU::LD_H_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regH = memoryUnit->readByte(HL);
	}

	void GBCPU::LD_H_A()
	{
		regH = regA;
	}

	void GBCPU::LD_L_B()
	{
		regL = regB;
	}

	void GBCPU::LD_L_C()
	{
		regL = regC;
	}

	void GBCPU::LD_L_D()
	{
		regL = regD;
	}

	void GBCPU::LD_L_E()
	{
		regL = regE;
	}

	void GBCPU::LD_L_H()
	{
		regL = regH;
	}

	void GBCPU::LD_L_L()
	{
		// nothing to do
	}

	void GBCPU::LD_L_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regL = memoryUnit->readByte(HL);
	}

	void GBCPU::LD_L_A()
	{
		regL = regA;
	}

	// 0x70 ~ 0x7F
	void GBCPU::LD_mHL_B()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regB);
	}

	void GBCPU::LD_mHL_C()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regC);
	}

	void GBCPU::LD_mHL_D()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regD);
	}
	void GBCPU::LD_mHL_E()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regE);
	}

	void GBCPU::LD_mHL_H()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regH);
	}

	void GBCPU::LD_mHL_L()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regL);
	}

	void GBCPU::HALT()
	{
		// TODO: implement this later
	}

	void GBCPU::LD_mHL_A()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regA);
	}

	void GBCPU::LD_A_B()
	{
		regA = regB;
	}

	void GBCPU::LD_A_C()
	{
		regA = regB;
	}

	void GBCPU::LD_A_D()
	{
		regA = regD;
	}

	void GBCPU::LD_A_E()
	{
		regA = regE;
	}

	void GBCPU::LD_A_H()
	{
		regA = regH;
	}

	void GBCPU::LD_A_L()
	{
		regA = regL;
	}

	void GBCPU::LD_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regA = memoryUnit->readByte(HL);
	}

	void GBCPU::LD_A_A()
	{
		// nothing  to do
	}

	// 0x80 ~ 0x8F
	void GBCPU::ADD_A_B()
	{
		byte sum = regA + regB;
		
		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regB));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADD_A_C()
	{
		byte sum = regA + regC;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regC));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADD_A_D()
	{
		byte sum = regA + regD;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regD));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADD_A_E()
	{
		byte sum = regA + regE;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regE));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADD_A_H()
	{
		byte sum = regA + regH;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regH));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}
	void GBCPU::ADD_A_L()
	{
		byte sum = regA + regL;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regL));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADD_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		byte tmp = memoryUnit->readByte(HL);
		byte sum = regA + tmp;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < tmp));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();
	}

	void GBCPU::ADD_A_A()
	{
		byte sum = regA << 1;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_B()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regB + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regB & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regB));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_C()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regC + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regC & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regC));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_D()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regD + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regD & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regD));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_E()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regE + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regE & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regE));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_H()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regH + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regH & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regH));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_L()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regL + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regL & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regL));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		byte tmp = memoryUnit->readByte(HL);

		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + tmp + carry;

		changeHalfCarryFlag((regA & 0x0F) + (tmp & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < tmp));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void GBCPU::ADC_A_A()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = (regA << 1) | carry;

		changeHalfCarryFlag((regA & 0x0F) + (regL & 0x0F) + carry > 0x0F);
		changeCarryFlag(regA > 0xEF);
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	// 0x90 ~ 0x9F
	void GBCPU::SUB_A_B()
	{
		byte diff = regA - regB;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regB));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SUB_A_C()
	{
		byte diff = regA - regC;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regC));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SUB_A_D()
	{
		byte diff = regA - regD;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regD));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SUB_A_E()
	{
		byte diff = regA - regE;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regE));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SUB_A_H()
	{
		byte diff = regA - regH;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regH));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SUB_A_L()
	{
		byte diff = regA - regL;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regL));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SUB_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		byte tmp = memoryUnit->readByte(HL);

		byte diff = regA - tmp;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > tmp));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SUB_A_A()
	{
		// regA - regA must be 0
		regA = 0;
		clearHalfCarryFlag();
		clearCarryFlag();
		setZeroFlag();
		setSubtractFlag();
	}

	void GBCPU::SBC_A_B()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regB - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regB & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regB));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SBC_A_C()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regC - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regC & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regC));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SBC_A_D()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regD - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regD & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regD));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SBC_A_E()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regE - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regE & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regE));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SBC_A_H()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regH - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regH & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regH));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SBC_A_L()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regL - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regL & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regL));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SBC_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		byte tmp = memoryUnit->readByte(HL);

		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - tmp - carry;

		changeHalfCarryFlag((regA & 0x0F) < (tmp & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > tmp));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void GBCPU::SBC_A_A()
	{
		if (getCarryFlag()) {
			clearZeroFlag();
			setSubtractFlag();
			setHalfCarryFlag();
			setCarryFlag();
			regA = 0xFF;
		} else {
			clearHalfCarryFlag();
			clearCarryFlag();
			setSubtractFlag();
			setZeroFlag();
			regA = 0;
		}
	}

	// 0xA0 ~ 0xAF
	void GBCPU::AND_B()
	{
		regA &= regB;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void GBCPU::AND_C();	
	void GBCPU::AND_D();	
	void GBCPU::AND_E();	
	void GBCPU::AND_H();	
	void GBCPU::AND_L();	
	void GBCPU::AND_mHL();	
	void GBCPU::AND_A();	
	void GBCPU::XOR_B();	
	void GBCPU::XOR_C();	
	void GBCPU::XOR_D();	
	void GBCPU::XOR_E();	
	void GBCPU::XOR_H();	
	void GBCPU::XOR_L();	
	void GBCPU::XOR_mHL();	
	void GBCPU::XOR_A();	
	// 0xB0 ~ 0xBF
	void OR_B();	
	void OR_C();	
	void OR_D();	
	void OR_E();	
	void OR_H();	
	void OR_L();	
	void OR_mHL();	
	void OR_A();	
	void CP_B();	
	void CP_C();	
	void CP_D();	
	void CP_E();	
	void CP_H();	
	void CP_L();	
	void CP_mHL();	
	void CP_A();	
	// 0xC0 ~ 0xCF
	void RET_nFZ();	
	void POP_BC();
	void JP_nFZ_nn();	
	void JP_nn();		
	void CALL_nFZ_nn();	
	void PUSH_BC();		
	void ADD_n();		
	void RST_0();		
	void RET_FZ();		
	void RET();			
	void JP_FZ_nn();	
	void CB_op_code();	
	void CALL_FZ_nn();	
	void CALL_nn();		
	void ADC_A_n();		
	void RST_8();		
	// 0xD0 ~ 0xDF
	void RET_nFC();		
	void POP_DE();		
	void JP_nFC_nn();	
	void Illegal_op_code_D3();	// !!! Illegal op code, should not be encountered
	void CALL_nFC_nn();	
	void PUSH_DE();		
	void SUB_A_n();		
	void RST_10();		
	void RET_FC();		
	void RETI();		
	void JP_FC_nn();	
	void Illegal_op_code_DB(); // !!! Illegal op code, should not be encountered
	void CALL_FC_nn();	// CALL FC, nn
	void Illegal_op_code_DD(); // !!! Illegal op code, should not be encountered
	void SBC_A_n();		// SBC A, n
	void RST_18();		// RST 0x18
	// 0xE0 ~ 0xEF
	void LDH_mn_A();	// LDH (n), A
	void POP_HL();		// POP HL
	void LD_mC_A();		// LD (C), A
	void Illegal_op_code_E3(); // !!! Illegal op code, should not be encountered
	void Illegal_op_code_E4(); // !!! Illegal op code, should not be encountered
	void PUSH_HL();		// PUSH HL
	void AND_n();		// AND n
	void RST_20();		// RST 0x20
	void ADD_SP_n();	// ADD SP, n
	void JP_mHL();		// JP (HL)
	void LD_n_A();		// LD n, A
	void Illegal_op_code_EB(); // !!! Illegal op code, should not be encountered
	void Illegal_op_code_EC(); // !!! Illegal op code, should not be encountered
	void Illegal_op_code_ED(); // !!! Illegal op code, should not be encountered
	void XOR_n();		// XOR n
	void RST_28();		// RST 0x28
	// 0xF0 ~ 0xFF
	void LDH_A_mn();	// LDH A, (n)
	void POP_AF();		// POP AF
	void LD_A_mC();		// LD A, (C)
	void DI();			// DI
	void Illegal_op_code_F4(); // !!! Illegal op code, should not be encountered
	void PUSH_AF();		// PUSH AF
	void OR_n();		// OR n
	void RST_30();		// RST 0x30
	void LDHL_SP_n();	// LDHL SP, n
	void LD_SP_HL();	// LD SP HL
	void LD_A_mnn();	// LD A, (nn)
	void EI();			// EI
	void Illegal_op_code_FC(); // !!! Illegal op code, should not be encountered
	void Illegal_op_code_FD(); // !!! Illegal op code, should not be encountered
	void CP_n();		// CP n
	void RST_38();		// RST 0x38
}
