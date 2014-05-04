#ifndef EMULATOR_H
#define EMULATOR_H

#include "CPU.h"
#include "Memory.h"
#include "Display.h"

#include <string>

namespace Chip8
{
class Emulator
{
public:
	Emulator();
	~Emulator();

	CPU &getCPU() { return cpu; }
	Memory &getMemory() { return memory; }
	Display &getDisplay() { return display; }

	bool isKeyPressed(byte_t key) { (void)key; return false; }
	bool isAnyKeyPressed() { return false; }
	byte_t getFirstKeyPressed() { return 0; }

	void init();

	void open(const std::string &filename);
	void close();

	void step(float seconds);

private:
	CPU cpu;
	Memory memory;
	Display display;
};
}

#endif // EMULATOR_H
