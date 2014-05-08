#ifndef SOUNDDEVICE_H
#define SOUNDDEVICE_H

#include "Sound.h"

#include <QtCore/QIODevice>

namespace Chip8GUI
{
class SoundDevice : public QIODevice
{
public:
	SoundDevice();
	~SoundDevice();

	void setInput(Chip8::Sound *sound);

protected:
	qint64 readData(char *data, qint64 maxlen) override;
	qint64 writeData(const char *data, qint64 len) override;

private:
	Chip8::Sound *input;
};
}

#endif // SOUNDDEVICE_H
