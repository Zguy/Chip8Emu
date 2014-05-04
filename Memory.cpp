#include "Memory.h"
#include "Log.h"

namespace Chip8
{
Memory::Memory()
{
	zeroAll();
}
Memory::~Memory()
{
}

void Memory::zeroAll()
{
	for (int i = 0; i < SIZE; ++i)
	{
		data[i] = 0;
	}
}

byte_t Memory::read(address_t address) const
{
	if (address >= 0 && address < SIZE)
	{
		return data[address];
	}
	Log::error() << "Address 0x" << std::hex << address << " is out of range" << std::endl;
	return 0;
}

void Memory::write(address_t address, byte_t byte)
{
	if (address >= 0 && address < SIZE)
	{
		data[address] = byte;
	}
	else
	{
		Log::error() << "Address 0x" << std::hex << address << " is out of range" << std::endl;
	}
}

byte_t *Memory::get(address_t address)
{
	if (address >= 0 && address < SIZE)
	{
		return &data[address];
	}
	Log::error() << "Address 0x" << std::hex << address << " is out of range" << std::endl;
	return nullptr;
}
}
