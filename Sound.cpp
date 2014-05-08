#include "Sound.h"

#include <cmath>

namespace Chip8
{
Sound::Sound() : sampleRate(44100)
{
	reset();
}
Sound::~Sound()
{
}

void Sound::reset()
{
	input = false;
	position = 0;
}

void Sound::setInput(bool input)
{
	this->input = input;
}

void Sound::readData(char *data, int size)
{
	static const float PI = 3.14159265358979323846f;
	static const float frequency = 440.f;

	for (int i = 0; i < size; ++i)
	{
		if (input)
			data[i] = static_cast<char>((std::sin(2.f * PI * frequency * position / static_cast<float>(sampleRate))) * 127.f);
		else
			data[i] = 0;
		++position;
	}
}
}
