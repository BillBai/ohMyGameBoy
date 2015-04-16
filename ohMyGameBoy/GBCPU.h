#pragma once

#include "GBTypes.h"
#include "GBMemoryUnit.h"

namespace GameBoy {
	class GBCPU
	{
	public:
		GBCPU();

		// register accessors
		byte getA() const { return regA; }
		byte getB() const { return regB; }
		byte getC() const { return regC; }
		byte getD() const { return regD; }
		byte getE() const { return regE; }
		byte getH() const { return regH; }
		byte getL() const { return regL; }
		word getSP() const { return regSP; }
		word getPC() const { return regPC; }

		// flag register accessors
		// Z | N | H | C | 0 | 0 | 0 | 0
		word getFlag()			const { return regFlag; }
		bool getZeroFlag()		const { return regFlag & 0x80; }
		bool getSubtractFlag()	const { return regFlag & 0x40; }
		bool getHalfCarryFlag() const { return regFlag & 0x20; }
		bool getCarryFlag()		const { return regFlag & 0x10; }

		~GBCPU();

	private:
		// general purpose registers
		byte regA, regB, regC, regD, regE, regH, regL;
		// stack pointer register
		word regSP;
		// program counter
		word regPC;
		// flag register
		byte regFlag;

		void setZeroFlag()			{ regFlag = regFlag | 0x80; }
		void clearZeroFlag()		{ regFlag = regFlag & 0x7F; }
		void setSubtractFlag()		{ regFlag = regFlag | 0x40; }
		void clearSubtractFlag()	{ regFlag = regFlag & 0xBF; }
		void setHalfCarryFlag()		{ regFlag = regFlag | 0x20; }
		void clearHalfCarryFlag()	{ regFlag = regFlag & 0xDF; }
		void setCarryFlag()			{ regFlag = regFlag | 0x10; }
		void clearCarryFlag()		{ regFlag = regFlag & 0xEF; }

		// Memory Unit
		GBMemoryUnit *memoryUnit;

		// GBCPU instructions
		// see http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html for details
		// 0x00 ~ 0x0F
		void NOP();			// 0x00 NOP
		void LD_BC_nn();	// 0x01 LD BC, nn
		void LD_mBC_A();	// 0x02 LD (BC), A
		void INC_BC();		// 0x03 INC BC
		void INC_B();		// 0x04 INC B
		void DEC_B();		// 0x05 DEC B
		void LD_B_n();		// 0x06 LD B, n
		void RLCA();		// 0x07 RLCA
		void LD_mnn_SP();	// 0x08 LD (nn), SP
		void ADD_HL_BC();	// 0x09 ADD HL, BC
		void LD_A_mBC();	// 0x0A LD A, (BC)
		void DEC_BC();		// 0x0B DEC BC
		void INC_C();		// 0x0C INC C
		void DEC_C();		// 0x0D DEC C
		void LD_C_n();		// 0x0E LD C, n
		void RRCA();		// 0x0F RRCA
	};
}

