#ifndef RANDOM_H
#define RANDOM_H

#include "Types.h"

namespace Random
{
using Chip8::byte_t;

unsigned int getSeed();
void setSeed(unsigned int seed);
void setRandomSeed();

byte_t get();
}

#endif // RANDOM_H
