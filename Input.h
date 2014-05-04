#ifndef INPUT_H
#define INPUT_H

#include "Types.h"

namespace Chip8
{
class Input
{
public:
	static const byte_t KEY_COUNT = 0xF;

	Input();
	~Input();

	void reset();

	void setPressed(byte_t key, bool pressed);

	bool isPressed(byte_t key) const;
	bool isAnyPressed() const;
	byte_t getFirstPressed() const;

private:
	bool keys[KEY_COUNT];
};
}

#endif // INPUT_H
