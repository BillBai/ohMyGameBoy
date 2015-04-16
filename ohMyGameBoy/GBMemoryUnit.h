#pragma once

#include <cstdint>

#include "GBTypes.h"

namespace GameBoy {
	class GBMemoryUnit
	{
	public:
		static const size_t GBMemroyCapacity = 0xffff;

		GBMemoryUnit();

		// Memory interface
		void writeByte(address addr, byte val);
		byte readByte(address addr);

		void writeWord(address addr, word val);
		word readWord(address addr);

		~GBMemoryUnit();
	private:
		uint8_t memory[GBMemroyCapacity];
	};
}


