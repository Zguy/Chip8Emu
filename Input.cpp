#include "Input.h"

namespace Chip8
{
Input::Input()
{
	reset();
}
Input::~Input()
{
}

void Input::reset()
{
	for (byte_t key = 0x0; key <= KEY_COUNT; ++key)
	{
		keys[key] = false;
	}
}

void Input::setPressed(byte_t key, bool pressed)
{
	if (key <= KEY_COUNT)
	{
		keys[key] = pressed;
	}
}

bool Input::isPressed(byte_t key) const
{
	if (key <= KEY_COUNT)
	{
		return keys[key];
	}
	return false;
}
bool Input::isAnyPressed() const
{
	for (byte_t key = 0x0; key <= KEY_COUNT; ++key)
	{
		if (isPressed(key))
			return true;
	}
	return false;
}
byte_t Input::getFirstPressed() const
{
	for (byte_t key = 0x0; key <= KEY_COUNT; ++key)
	{
		if (isPressed(key))
			return key;
	}
	return 0x0;
}
}
