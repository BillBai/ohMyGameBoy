#include <iostream>

#include "CPU.h"
#include "GBTypes.h"

int main(int argc, char **argv)
{
	std::cout << "Hello world!" << std::endl;
	GameBoy::CPU cpu = GameBoy::CPU();

	using GameBoy::byte;
	using GameBoy::word;

	byte h = 0x11;
	byte l = 0x88;

	auto r = GameBoy::combineByteToWord(h, l);

	getchar();
	return 0;
}