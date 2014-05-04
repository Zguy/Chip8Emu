#include "Random.h"

#include <random>

namespace
{
static std::mt19937 rng;
static unsigned int rngSeed = std::mt19937::default_seed;
}

namespace Random
{
unsigned int getSeed()
{
	return rngSeed;
}
void setSeed(unsigned int seed)
{
	rng.seed(seed);
	rngSeed = seed;
}
void setRandomSeed()
{
	std::random_device rd;
	setSeed(rd());
}

byte_t get()
{
	std::uniform_int_distribution<Chip8::byte_t> dist;
	return dist(rng);
}
}
