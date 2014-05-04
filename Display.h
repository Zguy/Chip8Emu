#ifndef DISPLAY_H
#define DISPLAY_H

#include "Types.h"

namespace Chip8
{
class Display
{
public:
	static const unsigned int WIDTH = 64;
	static const unsigned int HEIGHT = 32;
	static const unsigned int PIXEL_COUNT = WIDTH * HEIGHT;

	static const unsigned int SPRITE_WIDTH = 8;

	Display();
	~Display();

	void clear();

	///\return True if any pixel was unset
	bool drawSprite(unsigned int x, unsigned int y, byte_t *sprite, unsigned int height);

	const byte_t *getPixels() const { return pixels; }

private:
	byte_t pixels[PIXEL_COUNT];
};
}

#endif // DISPLAY_H
