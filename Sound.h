#ifndef SOUND_H
#define SOUND_H

namespace Chip8
{
class Sound
{
public:
	Sound();
	~Sound();

	void reset();

	inline void setSampleRate(int sampleRate) { this->sampleRate = sampleRate; }

	void setInput(bool input);

	void readData(char *data, int size);

private:
	int sampleRate;

	bool input;

	int position;
};
}

#endif // SOUND_H
