#include "GBMemoryUnit.h"

namespace GameBoy {
	GBMemoryUnit::GBMemoryUnit()
	{
	}

	// Memory interface
	// TODO: check address range
	void GBMemoryUnit::writeByte(address addr, byte val)
	{
		memory[addr] = val;
	}

	byte GBMemoryUnit::readByte(address addr)
	{
		return memory[addr];
	}

	void GBMemoryUnit::writeWord(address addr, word val)
	{
		memory[addr + 1] = getHighByte(val);
		memory[addr] = getLowByte(val);
	}

	word GBMemoryUnit::readWord(address addr)
	{
		byte h = memory[addr + 1];
		byte l = memory[addr];
		return combineByteToWord(h, l);
	}

	GBMemoryUnit::~GBMemoryUnit()
	{
	}
}

