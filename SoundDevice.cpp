#include "SoundDevice.h"

#include <cassert>

namespace Chip8GUI
{
SoundDevice::SoundDevice() : input(nullptr)
{
}
SoundDevice::~SoundDevice()
{
}

void SoundDevice::setInput(Chip8::Sound *sound)
{
	assert(sound != nullptr);
	this->input = sound;
}

qint64 SoundDevice::readData(char *data, qint64 maxlen)
{
	assert(input != nullptr);
	input->readData(data, maxlen);
	return maxlen;
}
qint64 SoundDevice::writeData(const char *data, qint64 len)
{
	Q_UNUSED(data)
	Q_UNUSED(len)
	return -1; // Read-only
}
}
