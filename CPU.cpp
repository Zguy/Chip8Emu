#include "CPU.h"
#include "Emulator.h"
#include "Types.h"
#include "Log.h"
#include "Random.h"
#include "Font.h"

#include <cassert>

namespace
{
using namespace Chip8;

inline int regX(opcode_t opcode)
{
	return ((opcode >> 8) & 0xF);
}
inline int regY(opcode_t opcode)
{
	return ((opcode >> 4) & 0xF);
}
}

namespace Chip8
{
CPU::CPU(Emulator *emu) : emu(emu)
{
	assert(emu != nullptr);
	reset();
}
CPU::~CPU()
{
}

void CPU::reset()
{
	pc = Memory::ROM_START;
	sp = 0;

	for (int i = 0; i < STACK_SIZE; ++i)
	{
		stack[i] = 0;
	}

	delayTimer = 0;
	soundTimer = 0;
	timeKeep = 0.f;

	I = 0;
	for (int i = 0; i < 16; ++i)
	{
		V[i] = 0;
	}
}

void CPU::step(float seconds)
{
	parseOpcode();
	tickTimers(seconds);

	emu->getSound().setInput(soundTimer > 0);
}

void CPU::parseOpcode()
{
	Memory &memory = emu->getMemory();

	opcode_t opcode = memory.read(pc);
	opcode <<= sizeof(byte_t)*8;
	opcode |= memory.read(pc+1);

	pc += sizeof(opcode_t);

	switch ((opcode >> 12) & 0xF)
	{
	case 0x0:
		switch (opcode & 0x0FFF)
		{
		case 0x0E0: emu->getDisplay().clear(); break;
		case 0x0EE: pc = pop(); break;
		default: unknownOpcode(opcode); break;
		}
		break;
	case 0x1: pc = (opcode & 0x0FFF); break;
	case 0x2: callSubroutine(opcode & 0x0FFF); break;
	case 0x3: if (V[regX(opcode)] == (opcode & 0x00FF)) skipInstruction(); break;
	case 0x4: if (V[regX(opcode)] != (opcode & 0x00FF)) skipInstruction(); break;
	case 0x5: if (V[regX(opcode)] == V[regY(opcode)]) skipInstruction(); break;
	case 0x6: V[regX(opcode)] = (opcode & 0x00FF); break;
	case 0x7: V[regX(opcode)] += (opcode & 0x00FF); break;
	case 0x8:
		switch (opcode & 0x000F)
		{
		case 0x0: V[regX(opcode)] = V[regY(opcode)]; break;
		case 0x1: V[regX(opcode)] |= V[regY(opcode)]; break;
		case 0x2: V[regX(opcode)] &= V[regY(opcode)]; break;
		case 0x3: V[regX(opcode)] ^= V[regY(opcode)]; break;
		case 0x4: V[regX(opcode)] = addSetCarry(V[regX(opcode)], V[regY(opcode)]); break;
		case 0x5: V[regX(opcode)] = subtractSetCarry(V[regX(opcode)], V[regY(opcode)]); break;
		case 0x6: V[regX(opcode)] = shiftRightSetCarry(V[regX(opcode)], 1); break;
		case 0x7: V[regX(opcode)] = subtractSetCarry(V[regY(opcode)], V[regX(opcode)]); break;
		case 0xE: V[regX(opcode)] = shiftLeftSetCarry(V[regX(opcode)], 1); break;
		default: unknownOpcode(opcode); break;
		}
		break;
	case 0x9: if (V[regX(opcode)] != V[regY(opcode)]) skipInstruction(); break;
	case 0xA: I = (opcode & 0x0FFF); break;
	case 0xB: pc = ((opcode & 0x0FFF) + V[0x0]); break;
	case 0xC: V[regX(opcode)] = Random::get() & (opcode & 0x00FF); break;
	case 0xD: V[0xF] = emu->getDisplay().drawSprite(V[regX(opcode)], V[regY(opcode)], emu->getMemory().get(I), (opcode & 0xF)) ? 1 : 0; break;
	case 0xE:
		switch (opcode & 0x00FF)
		{
		case 0x9E: if (emu->getInput().isPressed(V[regX(opcode)])) skipInstruction(); break;
		case 0xA1: if (!emu->getInput().isPressed(V[regX(opcode)])) skipInstruction(); break;
		default: unknownOpcode(opcode); break;
		}
		break;
	case 0xF:
		switch (opcode & 0x00FF)
		{
		case 0x07: V[regX(opcode)] = delayTimer; break;
		case 0x0A: if (emu->getInput().isAnyPressed()) V[regX(opcode)] = emu->getInput().getFirstPressed(); else repeatInstruction(); break;
		case 0x15: delayTimer = V[regX(opcode)]; break;
		case 0x18: soundTimer = V[regX(opcode)]; break;
		case 0x1E: I = addSetOverflow(I, V[regX(opcode)]); break;
		case 0x29: I = Memory::FONT_START + (V[regX(opcode)] * Font::HEIGHT); break;
		case 0x33: storeDecimal(I, V[regX(opcode)]); break;
		case 0x55: storeRegisters(I, regX(opcode)); break;
		case 0x65: fillRegisters(I, regX(opcode)); break;
		default: unknownOpcode(opcode); break;
		}
		break;
	default: unknownOpcode(opcode); break;
	}
}
void CPU::tickTimers(float seconds)
{
	timeKeep += seconds;

	static const float SECONDS_PER_TICK = (1.f / (float)TIMER_HZ);
	while (timeKeep >= SECONDS_PER_TICK)
	{
		timeKeep -= SECONDS_PER_TICK;
		if (delayTimer > 0)
			--delayTimer;
		if (soundTimer > 0)
			--soundTimer;
	}
}

void CPU::push(address_t address)
{
	if (sp >= STACK_SIZE)
	{
		Log::error() << "Stack overflow" << std::endl;
	}
	else
	{
		stack[sp] = address;
		++sp;
	}
}
address_t CPU::pop()
{
	if (sp <= 0)
	{
		Log::error() << "Stack underflow" << std::endl;
		return 0;
	}
	else
	{
		--sp;
		address_t top = stack[sp];
		return top;
	}
}

void CPU::storeRegisters(address_t address, int maxReg)
{
	Memory &memory = emu->getMemory();
	for (int i = 0x0; i <= maxReg; ++i)
	{
		memory.write(address + i, V[i]);
	}
}
void CPU::fillRegisters(address_t address, int maxReg)
{
	Memory &memory = emu->getMemory();
	for (int i = 0x0; i <= maxReg; ++i)
	{
		V[i] = memory.read(address + i);
	}
}

void CPU::storeDecimal(address_t address, byte_t byte)
{
	Memory &memory = emu->getMemory();
	byte_t hundreds = byte / 100;
	byte -= hundreds * 100;
	byte_t tens = byte / 10;
	byte -= tens * 10;
	byte_t ones = byte;
	memory.write(address + 0, hundreds);
	memory.write(address + 1, tens);
	memory.write(address + 2, ones);
}

void CPU::skipInstruction()
{
	pc += sizeof(opcode_t);
}
void CPU::repeatInstruction()
{
	pc -= sizeof(opcode_t);
}
void CPU::callSubroutine(address_t address)
{
	push(pc + sizeof(opcode_t));
	pc = address;
}

byte_t CPU::addSetCarry(byte_t v1, byte_t v2)
{
	int result = static_cast<int>(v1) + static_cast<int>(v2);
	V[0xF] = (result > 0xFF ? 1 : 0);
	return static_cast<byte_t>(result);
}
byte_t CPU::subtractSetCarry(byte_t v1, byte_t v2)
{
	V[0xF] = (v1 >= v2 ? 1 : 0);
	return v1 - v2;
}

address_t CPU::addSetOverflow(address_t v1, address_t v2)
{
	int result = static_cast<int>(v1) + static_cast<int>(v2);
	V[0xF] = (result > 0xFFFF ? 1 : 0);
	return static_cast<address_t>(result);
}

byte_t CPU::shiftRightSetCarry(byte_t v, int steps)
{
	V[0xF] = (v & 0x1);
	return (v >> steps);
}
byte_t CPU::shiftLeftSetCarry(byte_t v, int steps)
{
	V[0xF] = (v & 0x80);
	return (v << steps);
}

void CPU::unknownOpcode(opcode_t opcode)
{
	Log::error() << "Unknown opcode 0x" << std::hex << opcode << std::endl;
}
}
