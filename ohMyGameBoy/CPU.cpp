#include "CPU.h"

namespace GameBoy
{
	CPU::CPU():
        regPC(0x100),
        regSP(0xFFFE),
        regA(0x0),
        regB(0x0),
        regC(0x0),
        regD(0x0),
        regE(0x0),
        regH(0x0),
        regL(0x0),
        regFlag(0x0),
        machineCycleCount(0),
        clockCycleCount(0),
        IME(true)
	{

	}

	CPU::~CPU()
	{
	}

    void CPU::reset()
    {
        // TODO:
    }

	// nothing to do
	void CPU::NOP()
	{
	}

	void CPU::LD_BC_nn()
	{
		regC = memoryUnit->readByte(regSP);
		regB = memoryUnit->readByte(regSP + 1);
		regPC += 2;
	}

	void CPU::LD_mBC_A()
	{
		word addr = combineByteToWord(regB, regC);
		memoryUnit->writeByte(addr, regA);
	}

	void CPU::INC_BC()
	{
		word BC = combineByteToWord(regB, regC) + 1;
		regB = getHighByte(BC);
		regC = getLowByte(BC);
	}

	void CPU::INC_B()
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

	void CPU::DEC_B()
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

	void CPU::LD_B_n()
	{
		regB = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void CPU::RLCA()
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

	void CPU::LD_mnn_SP()
	{
		address addr = memoryUnit->readWord(regPC);
		memoryUnit->writeWord(addr, regSP);
		regPC += 2;
	}

	void CPU::ADD_HL_BC()
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

	void CPU::LD_A_mBC()
	{
		regA = memoryUnit->readByte(combineByteToWord(regB, regC));
	}

	void CPU::DEC_BC()
	{
		word tmp = combineByteToWord(regB, regC) - 1;
		regB = getHighByte(tmp);
		regC = getLowByte(tmp);
	}

	void CPU::INC_C()
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

	void CPU::DEC_C()
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

	void CPU::LD_C_n()
	{
		regC = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void CPU::RRCA()
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
	void CPU::STOP()
	{
		// TODO: handle stop
	}

	void CPU::LD_DE_nn()
	{
		regD = memoryUnit->readByte(regPC);
		regE = memoryUnit->readByte(regPC + 1);
		regPC += 2;
	}

	void CPU::LD_mDE_A()
	{
		address addr = combineByteToWord(regD, regE);
		memoryUnit->writeWord(addr, regA);
	}

	void CPU::INC_DE()
	{
		word tmp = combineByteToWord(regD, regE) + 1;
		regD = getHighByte(tmp);
		regE = getLowByte(tmp);
	}

	void CPU::INC_D()
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

	void CPU::DEC_D()
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

	void CPU::LD_D_n()
	{
		regD = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void CPU::RLA()
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

	void CPU::JR_n()
	{
		word offset = static_cast<int16_t>(memoryUnit->readByte(regPC));
		regPC = regPC + offset;
	}

	void CPU::ADD_HL_DE()
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

	void CPU::LD_A_mDE()
	{
		regA = memoryUnit->readByte(combineByteToWord(regD, regE));
	}

	void CPU::DEC_DE()
	{
		word DE = combineByteToWord(regD, regE) - 1;
		regD = getHighByte(DE);
		regE = getLowByte(DE);
	}

	void CPU::INC_E()
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

	void CPU::DEC_E()
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

	void CPU::LD_E_n()
	{
		regE = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void CPU::RRA()
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
	void CPU::JR_NZ_n()
	{
		if (!getZeroFlag()) {
			regPC = regPC + static_cast<int16_t>(memoryUnit->readByte(regPC));
		} else {
			regPC += 1;
		}
	}

	void CPU::LD_HL_nn()
	{
		regH = memoryUnit->readByte(regPC + 1);
		regL = memoryUnit->readByte(regPC);
		regPC += 2;
	}

	void CPU::LDI_mHL_A()
	{
		memoryUnit->writeWord(combineByteToWord(regH, regL), regA);
		word HL = combineByteToWord(regH, regL) + 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void CPU::INC_HL()
	{
		word HL = combineByteToWord(regH, regL) + 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void CPU::INC_H()
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
	
	void CPU::DEC_H()
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

	void CPU::LD_H_n()
	{
		regH = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void CPU::DAA()
	{
		// TODO:
	}

	void CPU::JR_Z_n()
	{
		if (getZeroFlag()) {
			regPC = regPC + static_cast<int16_t>(memoryUnit->readByte(regPC));
		} else {
			regPC += 1;
		}
	}

	void CPU::ADD_HL_HL()
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

	void CPU::LDI_A_mHL()
	{
		regA = memoryUnit->readByte(combineByteToWord(regH, regL));
		word HL = combineByteToWord(regH, regL) + 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void CPU::DEC_HL()
	{
		word HL = combineByteToWord(regH, regL) - 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void CPU::INC_L()
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

	void CPU::DEC_L()
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

	void CPU::LD_L_n()
	{
		regL = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void CPU::CPL()
	{
		regA ^= 0xFF;
		setSubtractFlag();
		setHalfCarryFlag();
	}

	// 0x30 ~ 0x3F
	void CPU::JR_NC_n()
	{
		if (!getCarryFlag()) {
			regPC = regPC + static_cast<int16_t>(memoryUnit->readByte(regPC));
		} else {
			regPC += 1;
		}
	}

	void CPU::LD_SP_nn()
	{
		byte high = memoryUnit->readByte(regPC + 1);
		byte low = memoryUnit->readByte(regPC);
		regSP = combineByteToWord(high, low);
	}

	void CPU::LDD_mHL_A()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regA);
		HL -= 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void CPU::INC_SP()
	{
		regSP += 1;
	}

	void CPU::INC_mHL()
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

	void CPU::DEC_mHL()
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

	void CPU::LD_mHL_n()
	{
		byte val = memoryUnit->readByte(regPC);
		word addr = combineByteToWord(regH, regL);
		memoryUnit->writeByte(addr, val);
		regPC += 1;
	}

	void CPU::SCF()
	{
		setCarryFlag();
		clearHalfCarryFlag();
		clearSubtractFlag();
	}

	void CPU::JR_C_n()
	{
		if (getCarryFlag()) {
			regPC = regPC + static_cast<int16_t>(memoryUnit->readByte(regPC));
		} else {
			regPC += 1;
		}
	}

	void CPU::ADD_HL_SP()
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

	void CPU::LDD_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regA = memoryUnit->readByte(HL);
		HL -= 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void CPU::DEC_SP()
	{
		regSP -= 1;
	}

	void CPU::INC_A()
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

	void CPU::DEC_A()
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

	void CPU::LD_A_n()
	{
		regA = memoryUnit->readByte(regPC);
		regPC += 1;
	}

	void CPU::CCF()
	{
		if (getCarryFlag()) {
			clearCarryFlag();
		} else {
			setCarryFlag();
		}

		clearHalfCarryFlag();
		clearSubtractFlag();
	}

	// 0x40 ~ 0x4F
	void CPU::LD_B_B()
	{
		// Nothing to be done
	}

	void CPU::LD_B_C()
	{
		regB = regC;
	}

	void CPU::LD_B_D()
	{
		regB = regD;
	}

	void CPU::LD_B_E()
	{
		regB = regE;
	}

	void CPU::LD_B_H()
	{
		regB = regH;
	}

	void CPU::LD_B_L()
	{
		regB = regL;
	}

	void CPU::LD_B_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regB = memoryUnit->readByte(HL);
	}

	void CPU::LD_B_A()
	{
		regB = regA;
	}

	void CPU::LD_C_B()
	{
		regC = regB;
	}

	void CPU::LD_C_C()
	{
		// Nothing to be done
	}

	void CPU::LD_C_D()
	{
		regC = regD;
	}

	void CPU::LD_C_E()
	{
		regC = regE;
	}

	void CPU::LD_C_H()
	{
		regC = regH;
	}

	void CPU::LD_C_L()
	{
		regC = regL;
	}

	void CPU::LD_C_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regC = memoryUnit->readByte(HL);
	}

	void CPU::LD_C_A()
	{
		regC = regA;
	}

	// 0x50 ~ 0x5F
	void CPU::LD_D_B()
	{
		regD = regB;
	}

	void CPU::LD_D_C()
	{
		regD = regC;
	}

	void CPU::LD_D_D()
	{
		// nothing to be done
	}

	void CPU::LD_D_E()
	{
		regD = regE;
	}

	void CPU::LD_D_H()
	{
		regD = regH;
	}

	void CPU::LD_D_L()
	{
		regD = regL;
	}

	void CPU::LD_D_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regD = memoryUnit->readByte(HL);
	}

	void CPU::LD_D_A()
	{
		regD = regA;
	}

	void CPU::LD_E_B()
	{
		regE = regB;
	}

	void CPU::LD_E_C()
	{
		regE = regC;
	}

	void CPU::LD_E_D()
	{
		regE = regD;
	}

	void CPU::LD_E_E()
	{
		// nothing to do
	}

	void CPU::LD_E_H()
	{
		regE = regH;
	}

	void CPU::LD_E_L()
	{
		regE = regL;
	}

	void CPU::LD_E_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regE = memoryUnit->readByte(HL);
	}

	void CPU::LD_E_A()
	{
		regE = regA;
	}

	// 0x60 ~ 0x6F
	void CPU::LD_H_B()
	{
		regH = regB;
	}

	void CPU::LD_H_C()
	{
		regH = regC;
	}

	void CPU::LD_H_D()
	{
		regH = regD;
	}

	void CPU::LD_H_E()
	{
		regH = regE;
	}

	void CPU::LD_H_H()
	{
		// nothing to do
	}

	void CPU::LD_H_L()
	{
		regH = regL;
	}

	void CPU::LD_H_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regH = memoryUnit->readByte(HL);
	}

	void CPU::LD_H_A()
	{
		regH = regA;
	}

	void CPU::LD_L_B()
	{
		regL = regB;
	}

	void CPU::LD_L_C()
	{
		regL = regC;
	}

	void CPU::LD_L_D()
	{
		regL = regD;
	}

	void CPU::LD_L_E()
	{
		regL = regE;
	}

	void CPU::LD_L_H()
	{
		regL = regH;
	}

	void CPU::LD_L_L()
	{
		// nothing to do
	}

	void CPU::LD_L_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regL = memoryUnit->readByte(HL);
	}

	void CPU::LD_L_A()
	{
		regL = regA;
	}

	// 0x70 ~ 0x7F
	void CPU::LD_mHL_B()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regB);
	}

	void CPU::LD_mHL_C()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regC);
	}

	void CPU::LD_mHL_D()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regD);
	}
	void CPU::LD_mHL_E()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regE);
	}

	void CPU::LD_mHL_H()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regH);
	}

	void CPU::LD_mHL_L()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regL);
	}

	void CPU::HALT()
	{
		// TODO: implement this later
	}

	void CPU::LD_mHL_A()
	{
		word HL = combineByteToWord(regH, regL);
		memoryUnit->writeByte(HL, regA);
	}

	void CPU::LD_A_B()
	{
		regA = regB;
	}

	void CPU::LD_A_C()
	{
		regA = regB;
	}

	void CPU::LD_A_D()
	{
		regA = regD;
	}

	void CPU::LD_A_E()
	{
		regA = regE;
	}

	void CPU::LD_A_H()
	{
		regA = regH;
	}

	void CPU::LD_A_L()
	{
		regA = regL;
	}

	void CPU::LD_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		regA = memoryUnit->readByte(HL);
	}

	void CPU::LD_A_A()
	{
		// nothing  to do
	}

	// 0x80 ~ 0x8F
	void CPU::ADD_A_B()
	{
		byte sum = regA + regB;
		
		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regB));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADD_A_C()
	{
		byte sum = regA + regC;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regC));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADD_A_D()
	{
		byte sum = regA + regD;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regD));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADD_A_E()
	{
		byte sum = regA + regE;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regE));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADD_A_H()
	{
		byte sum = regA + regH;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regH));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}
	void CPU::ADD_A_L()
	{
		byte sum = regA + regL;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < regL));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADD_A_mHL()
	{
		word HL = combineByteToWord(regH, regL);
		byte tmp = memoryUnit->readByte(HL);
		byte sum = regA + tmp;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < tmp));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();
	}

	void CPU::ADD_A_A()
	{
		byte sum = regA << 1;

		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADC_A_B()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regB + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regB & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regB));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADC_A_C()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regC + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regC & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regC));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADC_A_D()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regD + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regD & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regD));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADC_A_E()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regE + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regE & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regE));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADC_A_H()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regH + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regH & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regH));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADC_A_L()
	{
		byte carry = (getCarryFlag() ? 1 : 0);
		byte sum = regA + regL + carry;

		changeHalfCarryFlag((regA & 0x0F) + (regL & 0x0F) + carry > 0x0F);
		changeCarryFlag((sum < regA) || (sum < regL));
		changeZeroFlag(regA == 0);
		clearSubtractFlag();

		regA = sum;
	}

	void CPU::ADC_A_mHL()
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

	void CPU::ADC_A_A()
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
	void CPU::SUB_A_B()
	{
		byte diff = regA - regB;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regB));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SUB_A_C()
	{
		byte diff = regA - regC;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regC));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SUB_A_D()
	{
		byte diff = regA - regD;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regD));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SUB_A_E()
	{
		byte diff = regA - regE;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regE));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SUB_A_H()
	{
		byte diff = regA - regH;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regH));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SUB_A_L()
	{
		byte diff = regA - regL;

		changeHalfCarryFlag((regA & 0x0F) < (diff & 0x0F));
		changeCarryFlag((diff > regA) || (diff > regL));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SUB_A_mHL()
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

	void CPU::SUB_A_A()
	{
		// regA - regA must be 0
		regA = 0;
		clearHalfCarryFlag();
		clearCarryFlag();
		setZeroFlag();
		setSubtractFlag();
	}

	void CPU::SBC_A_B()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regB - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regB & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regB));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SBC_A_C()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regC - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regC & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regC));
		changeZeroFlag(diff == 0);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SBC_A_D()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regD - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regD & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regD));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SBC_A_E()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regE - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regE & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regE));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SBC_A_H()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regH - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regH & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regH));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SBC_A_L()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte diff = regA - regL - carry;

		changeHalfCarryFlag((regA & 0x0F) < (regL & 0x0F) + carry);
		changeCarryFlag((diff > regA) || (diff > regL));
		changeZeroFlag(diff);
		setSubtractFlag();

		regA = diff;
	}

	void CPU::SBC_A_mHL()
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

	void CPU::SBC_A_A()
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
	void CPU::AND_B()
	{
		regA &= regB;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::AND_C()
	{
		regA &= regC;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::AND_D()
	{
		regA &= regD;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::AND_E()
	{
		regA &= regE;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::AND_H()
	{
		regA &= regH;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::AND_L()
	{
		regA &= regL;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::AND_mHL()
	{
		byte tmp = memoryUnit->readByte(combineByteToWord(regH, regL));
		regA &= tmp;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::AND_A()
	{
		// regA & regA always equal regA, so regA remains same.
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_B()
	{
		regA ^= regB;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_C()
	{
		regA ^= regC;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_D()
	{
		regA ^= regD;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_E()
	{
		regA ^= regE;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_H()
	{
		regA ^= regH;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_L()
	{
		regA ^= regL;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_mHL()
	{
		byte tmp = memoryUnit->readByte(combineByteToWord(regH, regL));
		regA ^= tmp;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::XOR_A()
	{
		// a XOR a always be 0, so set regA to zero.
		regA = 0;
		setZeroFlag();
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	// 0xB0 ~ 0xBF
	void CPU::OR_B()
	{
		regA |= regB;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::OR_C()
	{
		regA |= regC;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::OR_D()
	{
		regA |= regD;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::OR_E()
	{
		regA |= regE;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::OR_H()
	{
		regA |= regH;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::OR_L()
	{
		regA |= regL;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::OR_mHL()
	{
		byte tmp = memoryUnit->readByte(combineByteToWord(regH, regL));
		regA |= tmp;
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::OR_A()
	{
		// a | a == a
		changeZeroFlag(regA == 0);
		clearHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::CP_B()
	{
		byte sum = regA - regB;
		changeHalfCarryFlag((sum &0x0F) > (regA & 0x0F));
		changeZeroFlag(sum == 0);
		setSubtractFlag();
		changeCarryFlag(regB > regA);
	}

	void CPU::CP_C()
	{
		byte sum = regA - regC;
		changeHalfCarryFlag((sum & 0x0F) > (regA & 0x0F));
		changeZeroFlag(sum == 0);
		setSubtractFlag();
		changeCarryFlag(regC > regA);
	}

	void CPU::CP_D()
	{
		byte sum = regA - regD;
		changeHalfCarryFlag((sum & 0x0F) > (regA & 0x0F));
		changeZeroFlag(sum == 0);
		setSubtractFlag();
		changeCarryFlag(regD > regA);
	}

	void CPU::CP_E()
	{
		byte sum = regA - regE;
		changeHalfCarryFlag((sum & 0x0F) > (regA & 0x0F));
		changeZeroFlag(sum == 0);
		setSubtractFlag();
		changeCarryFlag(regE > regA);
	}

	void CPU::CP_H()
	{
		byte sum = regA - regH;
		changeHalfCarryFlag((sum & 0x0F) > (regA & 0x0F));
		changeZeroFlag(sum == 0);
		setSubtractFlag();
		changeCarryFlag(regH > regA);
	}

	void CPU::CP_L()
	{
		byte sum = regA - regL;
		changeHalfCarryFlag((sum & 0x0F) > (regA & 0x0F));
		changeZeroFlag(sum == 0);
		setSubtractFlag();
		changeCarryFlag(regL > regA);
	}

	void CPU::CP_mHL()
	{
		byte tmp = memoryUnit->readByte(combineByteToWord(regH, regL));
		byte sum = regA - tmp;
		changeHalfCarryFlag((sum & 0x0F) > (regA & 0x0F));
		changeZeroFlag(sum == 0);
		setSubtractFlag();
		changeCarryFlag(tmp > regA);
	}

	void CPU::CP_A()
	{
		// a == a
		clearHalfCarryFlag();
		clearCarryFlag();
		setZeroFlag();
		setSubtractFlag();
	}

	// 0xC0 ~ 0xCF
	void CPU::RET_nFZ()
	{
		if (!getZeroFlag()) {
			regPC = memoryUnit->readWord(regSP);
			regSP += 2;
		}
	}

	void CPU::POP_BC()
	{
		regC = memoryUnit->readByte(regSP);
		regB = memoryUnit->readByte(regSP + 1);
		regSP += 2;
	}

	void CPU::JP_nFZ_nn()
	{
		if (!getZeroFlag()) {
			regPC = memoryUnit->readWord(regPC);
		} else {
			regPC += 2;
		}
	}

	void CPU::JP_nn()
	{
		regPC = memoryUnit->readWord(regPC);
	}

	void CPU::CALL_nFZ_nn()
	{
		if (!getZeroFlag()) {
			word targetPC = memoryUnit->readWord(regPC);
			regPC += 2;
			regSP -= 2;
			memoryUnit->writeWord(regSP, regPC);
			regPC = targetPC;
		} else {
			regPC += 2;
		}
	}

	void CPU::PUSH_BC()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, combineByteToWord(regB, regC));
	}

	void CPU::ADD_n()
	{
		byte tmp = memoryUnit->readByte(regPC);
		byte sum = regA + tmp;
		regPC += 1;
		
		changeHalfCarryFlag((sum & 0x0F) < (regA & 0x0F));
		changeCarryFlag((sum < regA) || (sum < tmp));
		
		regA = sum;
		changeZeroFlag(regA == 0);
		clearSubtractFlag();
	}

	void CPU::RST_0()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, regPC);
		regPC = 0;
	}

	void CPU::RET_FZ()
	{
		if (getZeroFlag()) {
			regPC = memoryUnit->readWord(regSP);
			regSP += 2;
		}
	}

	void CPU::RET()
	{
		regPC = memoryUnit->readWord(regSP);
		regSP += 2;
	}

	void CPU::JP_FZ_nn()
	{
		if (getZeroFlag()) {
			regPC = memoryUnit->readWord(regPC);
		} else {
			regPC += 2;
		}
	}

	void CPU::CB_op_code()
	{
		// TODO: run CB op codes
	}

	void CPU::CALL_FZ_nn()
	{
		if (getZeroFlag()) {
			word targetPC = memoryUnit->readWord(regPC);
			regPC += 2;
			regSP -= 2;
			memoryUnit->writeWord(regSP, regPC);
			regPC = targetPC;
		} else {
			regPC += 2;
		}
	}

	void CPU::CALL_nn()
	{
		word targetPC = memoryUnit->readWord(regPC);
		regPC += 2;
		regSP -= 2;
		memoryUnit->writeWord(regSP, regPC);
		regPC = targetPC;
	}

	void CPU::ADC_A_n()
	{
		byte carry = getCarryFlag() ? 1 : 0;
		byte tmp = memoryUnit->readByte(regPC);
		byte sum = regA + tmp + carry;
		regPC += 1;

		changeHalfCarryFlag(((regA & 0x0F) + (tmp & 0x0F) + carry) > 0x0F);
		changeCarryFlag((sum < regA) || (sum < tmp) || (sum < carry));

		regA = sum;
		changeZeroFlag(regA == 0);

		clearSubtractFlag();
	}

	void CPU::RST_8()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, regPC);
		regPC = 0x8;
	}

	// 0xD0 ~ 0xDF
	void CPU::RET_nFC()
	{
		if (!getZeroFlag()) {
			regPC = memoryUnit->readWord(regSP);
			regSP += 2;
		}
	}

	void CPU::POP_DE()
	{
		regD = memoryUnit->readByte(regSP + 1);
		regE = memoryUnit->readByte(regSP);
		regSP += 2;
	}

	void CPU::JP_nFC_nn()
	{
		if (!getZeroFlag()) {
			regPC = memoryUnit->readWord(regSP);
		} else {
			regPC += 2;
		}
	}

	void CPU::Illegal_op_code_D3()	// !!! Illegal op code, should not be encountered
	{
		// TODO: 
	}

	void CPU::CALL_nFC_nn()
	{
		if (!getCarryFlag()) {
			word targetPC = memoryUnit->readWord(regPC);
			regSP -= 2;
			memoryUnit->writeWord(regSP, regPC + 2); // store next instruction to stack
			regPC = targetPC;
		} else {
			regPC += 2;
		}
	}

	void CPU::PUSH_DE()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, combineByteToWord(regD, regE));
	}

	void CPU::SUB_A_n()
	{
		byte tmp = memoryUnit->readByte(regPC);
		byte sum = regA - tmp;
		regPC += 1;
		changeHalfCarryFlag((regA & 0x0F) < (sum & 0x0F));
		changeCarryFlag(tmp > regA);
		changeZeroFlag(sum == 0);
		regA = sum;
		clearSubtractFlag();
	}

	void CPU::RST_10()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, regPC);
		regPC = 0x10;
	}

	void CPU::RET_FC()
	{
		if (getCarryFlag()) {
			regPC = memoryUnit->readWord(regSP);
			regSP += 2;
		}
	}

	void CPU::RETI()
	{
		regPC = memoryUnit->readWord(regSP);
		regSP += 2;
		// TODO: modify the IRQ
	}

	void CPU::JP_FC_nn()
	{
		if (getCarryFlag()) {
			regPC = memoryUnit->readWord(regPC);
		}
		else {
			regPC += 2;
		}
	}

	void CPU::Illegal_op_code_DB() // !!! Illegal op code, should not be encountered
	{
		// TODO: alert and halt
	}

	void CPU::CALL_FC_nn()
	{
		if (getCarryFlag()) {
			word targetPC = memoryUnit->readWord(regPC);
			regSP -= 2;
			memoryUnit->writeWord(regSP, regPC + 2); // store next instruction to stack
			regPC = targetPC;
		}
		else {
			regPC += 2;
		}
	}

	void CPU::Illegal_op_code_DD() // !!! Illegal op code, should not be encountered
	{
		// TODO: alert and halt
	}

	void CPU::SBC_A_n()
	{
		byte tmp = memoryUnit->readByte(regPC);
		byte carry = getCarryFlag() ? 1 : 0;
		regPC += 1;
		byte sum = regA - tmp - carry;
		changeHalfCarryFlag((regA & 0x0F) < ((tmp & 0x0F) + carry));
		changeCarryFlag((regA < (tmp + carry)) || (tmp == 0xFF));
		changeZeroFlag(sum == 0);
		clearSubtractFlag();
		regA = sum;
	}

	void CPU::RST_18()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, regPC);
		regPC = 0x18;
	}

	// 0xE0 ~ 0xEF
	void CPU::LDH_mn_A()
	{
		word addr = 0xFF00 + static_cast<word>(memoryUnit->readByte(regPC));
		memoryUnit->writeByte(addr, regA);
		regPC += 1;
	}

	void CPU::POP_HL()
	{
		regH = memoryUnit->readByte(regSP + 1);
		regL = memoryUnit->readByte(regSP);
		regSP += 2;
	}

	void CPU::LD_mC_A()
	{
		word addr = 0xFF00 + static_cast<word>(regC);
		memoryUnit->writeByte(addr, regA);
	}
	void CPU::Illegal_op_code_E3() // !!! Illegal op code, should not be encountered
	{
		// TODO: alert and halt
	}
	void CPU::Illegal_op_code_E4() // !!! Illegal op code, should not be encountered
	{
		// TODO: alert and halt
	}

	void CPU::PUSH_HL()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, combineByteToWord(regH, regL));
	}

	void CPU::AND_n()
	{
		byte tmp = memoryUnit->readByte(regPC);
		regA &= tmp;
		regPC += 1;
		changeZeroFlag(regA == 0);
		setHalfCarryFlag();
		clearSubtractFlag();
		clearCarryFlag();
	}

	void CPU::RST_20()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, regPC);
		regPC = 0x20;
	}

	void CPU::ADD_SP_n()
	{
		byte tmp = static_cast<int16_t>(memoryUnit->readByte(regPC));
        regPC += 1;

        word sum = regSP + tmp;
        tmp = regSP ^ sum ^ tmp;
        regSP = sum;

        changeCarryFlag((tmp & 0x100) == 0x100);
        changeHalfCarryFlag((tmp & 0x10) == 0x10);

		clearZeroFlag();
		clearSubtractFlag();
	}

	void CPU::JP_mHL()
	{
		regPC = combineByteToWord(regH, regL);
	}
	void CPU::LD_mnn_A()
	{
		word addr = memoryUnit->readWord(regPC);
		memoryUnit->writeByte(addr, regA);
		regPC += 2;
	}
	void CPU::Illegal_op_code_EB() // !!! Illegal op code, should not be encountered
	{
		// TODO: alert and pause
	}

	void CPU::Illegal_op_code_EC() // !!! Illegal op code, should not be encountered
	{
		// TODO: alert and pause
	}
	void CPU::Illegal_op_code_ED() // !!! Illegal op code, should not be encountered
	{
		// TODO: alert and pause
	}

	void CPU::XOR_n()
	{
		regA ^= memoryUnit->readByte(regPC);
		regPC += 1;
		changeZeroFlag(regA == 0);
		clearSubtractFlag();
		clearHalfCarryFlag();
		clearCarryFlag();
	}

	void CPU::RST_28()
	{
		regSP -= 2;
		memoryUnit->writeWord(regSP, regPC);
		regPC = 0x28;
	}

	// 0xF0 ~ 0xFF
	void CPU::LDH_A_mn()
	{
		regA = memoryUnit->readByte(0xFF00u + regPC);
        regPC += 1;
	}

	void CPU::POP_AF()
    {
        byte regFValue = memoryUnit->readByte(regSP);
        changeZeroFlag(regFValue & ZeroFlagMask);
        changeSubtractFlag(regFValue & SubtractFlagMask);
        changeHalfCarryFlag(regFValue & HalfCarryFlagMask);
        changeCarryFlag(regFValue & CarryFlagMask);

        regA = memoryUnit->readByte(regSP + 1);
        regSP += 2;
    }

	void CPU::LD_A_mC()
    {
        regA = memoryUnit->readByte(0xFF00u + regC);
    }

	void CPU::DI()
    {
        // TODO:
        IME = false;
    }

	void CPU::Illegal_op_code_F4() // !!! Illegal op code, should not be encountered
    {
        // TODO: alert user
    }

	void CPU::PUSH_AF()
    {
        regSP -= 1;
        memoryUnit->writeByte(regSP, regA);
        regSP -= 1;
        memoryUnit->writeByte(regSP, regFlag);
    }

	void CPU::OR_n()
    {
        byte tmp = memoryUnit->readByte(regPC);
        regA = regA | tmp;
        changeCarryFlag(regA == 0);
        regPC += 1;

        clearSubtractFlag();
        clearCarryFlag();
        clearHalfCarryFlag();
    }

	void CPU::RST_30()
    {
        regSP -= 2;
        memoryUnit->writeWord(regSP, regPC);
        regPC = 0x30;
    }

	void CPU::LDHL_SP_n()
    {
        word tmp = static_cast<int16_t>(memoryUnit->readByte(regPC));
        regPC += 1;
        word HL = regSP + tmp;
        regH = getHighByte(HL);
        regL = getLowByte(HL);

        tmp = regSP ^ tmp ^ HL;
        changeCarryFlag((tmp & 0x100) == 0x100);
        changeHalfCarryFlag((tmp & 0x10) == 0x10);

        clearZeroFlag();
        clearSubtractFlag();
    }

	void CPU::LD_SP_HL()
    {
        regSP = combineByteToWord(regH, regL);
    }

	void CPU::LD_A_mnn()
    {
        word addr = combineByteToWord(memoryUnit->readByte(regPC + 1), memoryUnit->readByte(regPC));
        regA = memoryUnit->readByte(addr);
        regPC += 2;
    }

	void CPU::EI()
    {
        // TODO:
        IME = true;
    }

	void CPU::Illegal_op_code_FC() // !!! Illegal op code, should not be encountered
    {
        // TODO: alert
    }
	void CPU::Illegal_op_code_FD() // !!! Illegal op code, should not be encountered
    {
        // TODO: alert
    }

	void CPU::CP_n()
    {
        byte tmp = memoryUnit->readByte(regPC);
        regPC += 1;

        byte sum = regA - tmp;
        changeHalfCarryFlag((sum & 0x0F) > (regA & 0x0F));
        changeCarryFlag(regA < tmp);
        setSubtractFlag();
    }

	void CPU::RST_38()
    {
        regSP -= 2;
        memoryUnit->writeWord(regSP, regPC);
        regPC = 0x38;
    }

    // CB instructions
    // 0x00 ~ 0x0F

    void CPU::RLC_B()
    {
        byte msb = (regB & 0x80) ? 0x1 : 0x0;
        regB = (regB << 1) | msb;
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regB == 0x0);
    }

    void CPU::RLC_C()
    {
        byte msb = (regC & 0x80) ? 0x1 : 0x0;
        regC = (regC << 1) | msb;
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regC == 0x0);
    }

    void CPU::RLC_D()
    {
        byte msb = (regD & 0x80) ? 0x1 : 0x0;
        regD = (regD << 1) | msb;
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regD == 0x0);
    }

    void CPU::RLC_E()
    {
        byte msb = (regE & 0x80) ? 0x1 : 0x0;
        regE = (regE << 1) | msb;
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regE == 0x0);
    }

    void CPU::RLC_H()
    {
        byte msb = (regH & 0x80) ? 0x1 : 0x0;
        regH = (regH << 1) | msb;
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regH == 0x0);
    }

    void CPU::RLC_L()
    {
        byte msb = (regL & 0x80) ? 0x1 : 0x0;
        regL = (regL << 1) | msb;
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regL == 0x0);
    }

    void CPU::RLC_mHL()
    {
        word HL = combineByteToWord(regH, regL);
        byte tmp = memoryUnit->readByte(HL);
        byte msb = (tmp & 0x80) ? 0x1 : 0x0;
        tmp = (tmp << 1) | msb;
        memoryUnit->writeByte(HL, tmp);
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(tmp == 0x0);
    }

    void CPU::RLC_A()
    {
        byte msb = (regA & 0x80) ? 0x1 : 0x0;
        regA = (regA << 1) | msb;
        changeCarryFlag(msb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regA == 0x0);
    }

    void CPU::RRC_B()
    {
        byte lsb = (regB & 0x01) ? 0x80 : 0x00;
        regB = lsb | (regB >> 1);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regB == 0x0);
    }

    void CPU::RRC_C()
    {
        byte lsb = (regC & 0x01) ? 0x80 : 0x00;
        regC = lsb | (regC >> 1);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regC == 0x0);
    }

    void CPU::RRC_D()
    {
        byte lsb = (regD & 0x01) ? 0x80 : 0x00;
        regD = lsb | (regD >> 1);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regD == 0x0);
    }

    void CPU::RRC_E()
    {
        byte lsb = (regE & 0x01) ? 0x80 : 0x00;
        regE = lsb | (regE >> 1);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regE == 0x0);
    }

    void CPU::RRC_H()
    {
        byte lsb = (regH & 0x01) ? 0x80 : 0x00;
        regH = lsb | (regH >> 1);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regH == 0x0);
    }

    void CPU::RRC_L()
    {
        byte lsb = (regL & 0x01) ? 0x80 : 0x00;
        regL = lsb | (regL >> 1);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regL == 0x0);
    }

    void CPU::RRC_mHL()
    {
        word HL = combineByteToWord(regH, regL);
        byte tmp = memoryUnit->readByte(HL);
        byte lsb = (tmp & 0x01) ? 0x80 : 0x00;
        tmp = lsb | (tmp >> 1);
        memoryUnit->writeByte(HL, tmp);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(tmp == 0x0);
    }

    void CPU::RRC_A()
    {
        byte lsb = (regA & 0x01) ? 0x80 : 0x00;
        regA = lsb | (regA >> 1);
        changeCarryFlag(lsb);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regA == 0x0);
    }

    void CPU::RL_B()
    {
        bool carry = (regB & 0x80) != 0;
        regB = (regB << 1) | getCarryFlag() ? 0x01 : 0x00;
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regB == 0x0);
    }

    void CPU::RL_C()
    {
        bool carry = (regC & 0x80) != 0;
        regC = (regC << 1) | getCarryFlag() ? 0x01 : 0x00;
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regC == 0x0);
    }

    void CPU::RL_D()
    {
        bool carry = (regD & 0x80) != 0;
        regD = (regD << 1) | getCarryFlag() ? 0x01 : 0x00;
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regD == 0x0);
    }

    void CPU::RL_E()
    {
        bool carry = (regE & 0x80) != 0;
        regE = (regE << 1) | getCarryFlag() ? 0x01 : 0x00;
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regE == 0x0);
    }

    void CPU::RL_H()
    {
        bool carry = (regH & 0x80) != 0;
        regH = (regH << 1) | getCarryFlag() ? 0x01 : 0x00;
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regH == 0x0);
    }

    void CPU::RL_L()
    {
        bool carry = (regL & 0x80) != 0;
        regL = (regL << 1) | getCarryFlag() ? 0x01 : 0x00;
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regL == 0x0);
    }

    void CPU::RL_mHL()
    {
        word HL = combineByteToWord(regH, regL);
        byte tmp = memoryUnit->readByte(HL);
        bool carry = (tmp & 0x80) != 0;
        tmp = (tmp << 1) | getCarryFlag() ? 0x01 : 0x00;
        memoryUnit->writeByte(HL, tmp);
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(tmp == 0x0);
    }

    void CPU::RL_A()
    {
        bool carry = (regA & 0x80) != 0;
        regA = (regA << 1) | getCarryFlag() ? 0x01 : 0x00;
        changeCarryFlag(carry);
        clearHalfCarryFlag();
        clearSubtractFlag();
        changeZeroFlag(regA == 0x0);
    }

    void CPU::RR_B()
    {
        bool carry = (regB & 0x01) != 0;
        regB = (getCarryFlag() ? 0x80 : 0x00) | (regB >> 1);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(regB == 0x0);
    }

    void CPU::RR_C()
    {
        bool carry = (regC & 0x01) != 0;
        regC = (getCarryFlag() ? 0x80 : 0x00) | (regC >> 1);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(regC == 0x0);
    }

    void CPU::RR_D()
    {
        bool carry = (regD & 0x01) != 0;
        regD = (getCarryFlag() ? 0x80 : 0x00) | (regD >> 1);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(regD == 0x0);
    }

    void CPU::RR_E()
    {
        bool carry = (regE & 0x01) != 0;
        regE = (getCarryFlag() ? 0x80 : 0x00) | (regE >> 1);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(regE == 0x0);
    }

    void CPU::RR_H()
    {
        bool carry = (regH & 0x01) != 0;
        regH = (getCarryFlag() ? 0x80 : 0x00) | (regH >> 1);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(regH == 0x0);
    }

    void CPU::RR_L()
    {
        bool carry = (regL & 0x01) != 0;
        regL = (getCarryFlag() ? 0x80 : 0x00) | (regL >> 1);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(regL == 0x0);
    }

    void CPU::RR_mHL()
    {
        word HL = combineByteToWord(regH, regL);
        byte tmp = memoryUnit->readByte(HL);
        bool carry = (tmp & 0x01) != 0;
        tmp = (getCarryFlag() ? 0x80 : 0x00) | (tmp >> 1);
        memoryUnit->writeByte(HL, tmp);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(tmp == 0x0);
    }

    void CPU::RR_A()
    {
        bool carry = (regA & 0x01) != 0;
        regA = (getCarryFlag() ? 0x80 : 0x00) | (regA >> 1);
        changeCarryFlag(carry);
        clearSubtractFlag();
        clearHalfCarryFlag();
        changeZeroFlag(regA == 0x0);
    }
}
