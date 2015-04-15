#pragma once

#include <cstdint>

#include "GBMemoryUnit.h"

class GBCPU
{
public:
	using address = uint16_t;
	using byte = uint8_t;
	using word = uint16_t;

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
	word Flag() { return regFlag; }
	

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
};
