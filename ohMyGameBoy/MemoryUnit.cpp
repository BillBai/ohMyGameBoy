#include "MemoryUnit.h"

namespace GameBoy {
	MemoryUnit::MemoryUnit()
	{
	}

	// Memory interface
	// TODO: check address range
	void MemoryUnit::writeByte(address addr, byte val)
	{
		memory[addr] = val;
	}

	byte MemoryUnit::readByte(address addr)
	{
		return memory[addr];
	}

	void MemoryUnit::writeWord(address addr, word val)
	{
		memory[addr + 1] = getHighByte(val);
		memory[addr] = getLowByte(val);
	}

	word MemoryUnit::readWord(address addr)
	{
		byte h = memory[addr + 1];
		byte l = memory[addr];
		return combineByteToWord(h, l);
	}

	MemoryUnit::~MemoryUnit()
	{
	}
}

