#pragma once

#include <cstdint>

#include "GBTypes.h"
#include "GBMemoryUnit.h"

namespace GameBoy {
	class GBCPU
	{
	public:
		GBCPU();

		// register accessors
		byte A() { return regA; }
		byte B() { return regB; }
		byte C() { return regC; }
		byte D() { return regD; }
		byte E() { return regE; }
		byte H() { return regH; }
		byte L() { return regL; }
		word SP() { return regSP; }
		word PC() { return regPC; }

		// flag register accessors
		// Z | N | H | C | 0 | 0 | 0 | 0
		word Flag() { return regFlag; }
		bool ZeroFlag() { return regFlag & 0x80;  }
		bool SubtractFlag() { return regFlag & 0x40; }
		bool HalfCarryFlag() { return regFlag & 0x20; }
		bool CarryFlag() { return regFlag & 0x10; }

		virtual ~GBCPU();

	private:
		// general purpose registers
		byte regA, regB, regC, regD, regE, regH, regL;
		// stack pointer register
		word regSP;
		// program counter
		word regPC;
		// flag register
		byte regFlag;

		// Memory Unit
		GBMemoryUnit *memoryUnit;

		// GBCPU instructions

		void NOP();
		void LD_BC_
	};
}

