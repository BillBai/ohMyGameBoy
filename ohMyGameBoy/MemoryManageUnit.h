#pragma once

#include <cstdint>
#include <stddef.h>

#include "GBTypes.h"

namespace GameBoy {
	class MemoryManageUnit
	{
	public:
		static const size_t GBMemoryCapacity = 0xffff;

		MemoryManageUnit();

		// Memory interface
		void writeByte(address addr, byte val);
		byte readByte(address addr);

		void writeWord(address addr, word val);
		word readWord(address addr);

		~MemoryManageUnit();
	private:
		uint8_t memory[GBMemoryCapacity];
	};
}


