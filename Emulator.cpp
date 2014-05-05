#include "Emulator.h"
#include "Log.h"
#include "Font.h"

#include <fstream>

namespace Chip8
{
Emulator::Emulator() : cpu(this)
{
	init();
}
Emulator::~Emulator()
{
}

void Emulator::init()
{
	// Load font
	for (int i = 0; i < (Font::COUNT*Font::HEIGHT); ++i)
	{
		memory.write(Memory::FONT_START + i, Font::DATA[i]);
	}
}

bool Emulator::open(const std::string &filename)
{
	close();
	init();

	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		Log::error() << "Could not open \"" << filename << "\"" << std::endl;
		return false;
	}

	std::size_t size = file.tellg();
	file.seekg(0);

	if (size > (Memory::SIZE - Memory::ROM_START))
	{
		Log::error() << "ROM file is too large (maximum size " << std::dec << (Memory::SIZE - Memory::ROM_START) << " bytes)" << std::endl;
		return false;
	}

	byte_t *data = memory.get(Memory::ROM_START);
	file.read(reinterpret_cast<char*>(data), size);

	return true;
}
void Emulator::close()
{
	memory.zeroAll();
	cpu.reset();
	display.clear();
}

void Emulator::step(float seconds)
{
	cpu.step(seconds);
}
}
