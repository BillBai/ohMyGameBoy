#include "MemoryManageUnit.h"

namespace GameBoy {
	MemoryManageUnit::MemoryManageUnit()
	{
	}

	// Memory interface
	// TODO: check address range
	void MemoryManageUnit::writeByte(address addr, byte val)
	{
		memory[addr] = val;
	}

	byte MemoryManageUnit::readByte(address addr)
	{
		return memory[addr];
	}

	void MemoryManageUnit::writeWord(address addr, word val)
	{
		memory[addr + 1] = getHighByte(val);
		memory[addr] = getLowByte(val);
	}

	word MemoryManageUnit::readWord(address addr)
	{
		byte h = memory[addr + 1];
		byte l = memory[addr];
		return combineByteToWord(h, l);
	}

	MemoryManageUnit::~MemoryManageUnit()
	{
	}
}

