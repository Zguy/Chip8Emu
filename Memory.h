#ifndef MEMORY_H
#define MEMORY_H

#include "Types.h"

namespace Chip8
{
class Memory
{
public:
	static const int SIZE = 0x1000;
	static const address_t FONT_START = 0x0;
	static const address_t ROM_START = 0x200;

	Memory();
	~Memory();

	void zeroAll();

	byte_t read(address_t address) const;
	void write(address_t address, byte_t);

	byte_t *get(address_t address);

private:
	byte_t data[SIZE];
};
}

#endif // MEMORY_H
