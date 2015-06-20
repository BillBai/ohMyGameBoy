#pragma once

#include <cstdint>
#include <stddef.h>

#include "GBTypes.h"

namespace GameBoy {
	class MemoryUnit
	{
	public:
		static const size_t GBMemoryCapacity = 0xffff;


		MemoryUnit();

		// Memory interface
		void writeByte(address addr, byte val);
		byte readByte(address addr);

		void writeWord(address addr, word val);
		word readWord(address addr);

		~MemoryUnit();
	private:
		uint8_t memory[GBMemoryCapacity];
	};
}


