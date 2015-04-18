#include <iostream>

#include "GBCPU.h"
#include "GBTypes.h"

int main(int argc, char **argv)
{
	std::cout << "Hello world!" << std::endl;
	GameBoy::GBCPU cpu = GameBoy::GBCPU();

	using GameBoy::byte;
	using GameBoy::word;

	byte h = 0x11;
	byte l = 0x88;

	word r = GameBoy::combineByteToWord(h, l);

	getchar();
	return 0;
}