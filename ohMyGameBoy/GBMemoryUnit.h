#pragma once

#include <cstdint>

#include "GBCPU.h"

class GBMemoryUnit
{
public:
	static const int GBMemroyCapacity = 0xffff;

	// Memory interface
	void writeByte(GBCPU::address address, GBCPU::byte value);
	GBCPU::byte readByte(GBCPU::address address);
	
	void writeWord(GBCPU::address address, GBCPU::word value);
	GBCPU::word readWord(GBCPU::address address);

	GBMemoryUnit();
	~GBMemoryUnit();
private:
	uint8_t memory[GBMemroyCapacity];
};

