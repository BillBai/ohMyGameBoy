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
		byte HL = combineByteToWord(regH, regL) + 1;
		regH = getHighByte(HL);
		regL = getLowByte(HL);
	}

	void GBCPU::INC_HL()
	{
		byte HL = combineByteToWord(regH, regL) + 1;
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
		}
		else {
			clearZeroFlag();
		}

		if ((regH & 0x0F) == 0) {
			setHalfCarryFlag();
		}
		else {
			clearHalfCarryFlag();
		}

		setSubtractFlag();
	}

	void LD_H_n();
	void DAA();
	void JR_Z_n();
	void ADD_HL_HL();
	void LDI_A_mHL();
	void DEC_HL();
	void INC_L();
	void DEC_L();
	void LD_L_n();
	void CPL();
	// 0x30 ~ 0x3F
	void JR_NC_n();
	void LD_SP_nn();
	void LDD_mHL_A();
	void INC_SP();
	void INC_mHL();
	void DEC_mHL();
	void LD_mHL_n();
	void SCF();
	void JR_C_n();
	void ADD_HL_SP();
	void LDD_A_mHL();
	void DEC_A();
	void INC_A();
	void DEC_A();
	void LD_A_n();
	void CCF();
	// 0x40 ~ 0x4F
	void LD_B_B();
	void LD_B_C();
	void LD_B_D();
	void LD_B_E();
	void LD_B_H();
	void LD_B_L();
	void LD_B_mHL();
	void LD_B_A();
	void LD_C_B();
	void LD_C_C();
	void LD_C_D();
	void LD_C_E();
	void LD_C_H();
	void LD_C_L();
	void LD_C_mHL();
	void LD_C_A();
	// 0x50 ~ 0x5F
	void LD_D_B();
	void LD_D_C();
	void LD_D_D();
	void LD_D_E();
	void LD_D_H();
	void LD_D_L();
	void LD_D_mHL();
	void LD_D_A();
	void LD_E_B();
	void LD_E_C();
	void LD_E_D();
	void LD_E_E();
	void LD_E_H();
	void LD_E_L();
	void LD_E_mHL();
	void LD_E_A();
}
