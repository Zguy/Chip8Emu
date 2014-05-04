#include "Display.h"

namespace
{
inline int index(int x, int y, int width)
{
	return (y * width + x);
}
}

namespace Chip8
{
Display::Display()
{
	clear();
}
Display::~Display()
{
}

void Display::clear()
{
	for (unsigned int i = 0; i < PIXEL_COUNT; ++i)
	{
		pixels[i] = 0;
	}
}

bool Display::drawSprite(unsigned int x, unsigned int y, byte_t *sprite, unsigned int height)
{
	bool unset = false;

	for (unsigned int yi = 0; yi < height; ++yi)
	{
		byte_t row = sprite[yi];
		for (unsigned int xi = 0; xi < SPRITE_WIDTH; ++xi)
		{
			if (x+xi < WIDTH && y+yi < HEIGHT)
			{
				byte_t spritePixel = (row & (0x80 >> xi));
				byte_t &displayPixel = pixels[index(x+xi,y+yi,WIDTH)];

				if (spritePixel != 0)
				{
					if (displayPixel != 0)
						unset = true;

					displayPixel ^= 1;
				}
			}
		}
	}

	return unset;
}
}
