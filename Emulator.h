#ifndef EMULATOR_H
#define EMULATOR_H

#include "CPU.h"
#include "Memory.h"
#include "Display.h"
#include "Input.h"
#include "Sound.h"

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
	Input &getInput() { return input; }
	Sound &getSound() { return sound; }

	void init();

	bool open(const std::string &filename);
	void close();

	void step(float seconds);

private:
	CPU cpu;
	Memory memory;
	Display display;
	Input input;
	Sound sound;
};
}

#endif // EMULATOR_H
