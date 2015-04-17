#include "GBCPU.h"

namespace GameBoy {
	GBCPU::GBCPU()
	{
	}

	GBCPU::~GBCPU()
	{
	}

	// nothing to do
	void GBCPU::NOP()
	{}

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

		if (regB == 0) { setZeroFlag(); } 
		else { clearZeroFlag(); }

		if ((regB & 0x0F) == 0) { setHalfCarryFlag(); }
		else { clearHalfCarryFlag(); }

		clearSubtractFlag();
	}

	void GBCPU::DEC_B()
	{
		regB -= 1;

		if (regB == 0) { setZeroFlag(); }
		else { clearZeroFlag(); }

		if ((regB & 0x0F) == 0) { setHalfCarryFlag(); }
		else { clearHalfCarryFlag(); }

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
		if (regA > 0x7F) { setCarryFlag(); }
		else { clearCarryFlag(); }

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
		regH = getHighByte(sum);
		regL = getLowByte(sum);

		clearSubtractFlag();
		if (regL > getLowByte(sum)) { setHalfCarryFlag(); }
		else { clearHalfCarryFlag(); }
		if (sum < HL || sum < BC) { setCarryFlag(); }
		else { clearCarryFlag(); }
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

		if (regC == 0) { setZeroFlag(); }
		else { clearZeroFlag(); }

		if ((regC & 0x0F) == 0) { setHalfCarryFlag(); }
		else { clearHalfCarryFlag(); }

		clearSubtractFlag();
	}

	void GBCPU::DEC_C()
	{
		regC -= 1;

		if (regC == 0) { setZeroFlag(); }
		else { clearZeroFlag(); }

		if ((regC & 0x0F) == 0x0F) { setHalfCarryFlag(); }
		else { clearHalfCarryFlag(); }

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

		if (regA > 0x7F) { setCarryFlag(); }
		else { clearCarryFlag(); }

		clearZeroFlag();
		clearSubtractFlag();
		clearHalfCarryFlag();
	}

	void GBCPU::STOP()
	{
		// TODO: handle stop
	}

	// 0x10 ~ 0x1F
	void STOP();
	void LD_DE_nn();
	void LD_mDE_A();
	void INC_DE();
	void INC_D();
	void DEC_D();
	void LD_D_n();
	void RLA();
	void JR_n();
	void ADD_HL_DE();
	void LD_A_mDE();
	void DEC_DE();
	void INC_E();
	void DEC_E();
	void LD_E_n();
	void RRA();
	// 0x20 ~ 0x2F
	void JR_NZ_n();
	void LD_HL_nn();
	void LDI_mHL_A();
	void INC_HL();
	void INC_H();
	void DEC_H();
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
