#include "GBMemoryUnit.h"


GBMemoryUnit::GBMemoryUnit()
{
}

// Memory interface
// TODO: check address range
void GBMemoryUnit::writeByte(GBCPU::address address, GBCPU::byte value)
{
	memory[address] = value;
}

GBCPU::byte GBMemoryUnit::readByte(GBCPU::address address)
{
	return memory[address];
}

void GBMemoryUnit::writeWord(GBCPU::address address, GBCPU::word value)
{
	memory[address] = value;
}

GBCPU::word GBMemoryUnit::readWord(GBCPU::address address)
{
	return memory[address];
}

GBMemoryUnit::~GBMemoryUnit()
{
}
