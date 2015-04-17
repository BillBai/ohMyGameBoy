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
}
