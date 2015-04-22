#pragma once

#include <cstdint>

namespace GameBoy {
	using address = uint16_t;
	using byte = uint8_t;
	using word = uint16_t;

	// helpers

	inline byte getHighByte(word w)
	{
		return static_cast<byte>((w >> 8) & 0x00FF);
	}

	inline byte getLowByte(word w)
	{
		return static_cast<byte>(w & 0x00FF);
	}

	inline word combineByteToWord(byte h, byte l)
	{
		word wh = static_cast<word>(h);
		return static_cast<word>((wh << 8) | l);
	}
}
