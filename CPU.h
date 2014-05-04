#ifndef CPU_H
#define CPU_H

#include "Types.h"

#include <cstdint>

namespace Chip8
{
class Emulator;

class CPU
{
public:
	explicit CPU(Emulator *emu);
	~CPU();

	void reset();

	void step(float seconds);

private:
	void parseOpcode();
	void tickTimers(float seconds);

	void push(address_t address);
	address_t pop();

	void storeRegisters(address_t address, int maxReg);
	void fillRegisters(address_t address, int maxReg);

	void storeDecimal(address_t address, byte_t byte);

	void skipInstruction();
	void repeatInstruction();
	void callSubroutine(address_t address);

	byte_t addSetCarry(byte_t v1, byte_t v2);
	byte_t subtractSetCarry(byte_t v1, byte_t v2);

	address_t addSetOverflow(address_t v1, address_t v2);

	byte_t shiftRightSetCarry(byte_t v, int steps);
	byte_t shiftLeftSetCarry(byte_t v, int steps);

	void unknownOpcode(opcode_t opcode);

	Emulator *emu;

	address_t pc;
	int sp;

	static const int STACK_SIZE = 16;
	address_t stack[STACK_SIZE];

	static const int TIMER_HZ = 60;
	byte_t delayTimer;
	byte_t soundTimer;
	float timeKeep;

	address_t I;
	byte_t V[16];
};
}

#endif // CPU_H
