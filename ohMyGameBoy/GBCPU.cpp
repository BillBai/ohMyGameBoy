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
		word offset = (word)memoryUnit->readByte(regPC);
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
}
