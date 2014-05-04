#ifndef FLAGHELPERS_H
#define FLAGHELPERS_H

#include <climits>

namespace FlagHelpers
{
using Chip8::byte_t;

template<typename T> inline int bits()
{
	return (sizeof(T) * CHAR_BIT) - 1;
}

template<typename T> inline T neg(T i)
{
	return (i >> bits<T>());
}
template<typename T> inline T pos(T i)
{
	return ((~i) >> bits<T>());
}
template<typename T> inline bool addCarry(T a, T b, T c)
{
	return ((neg(a) & neg(b)) | (neg(a) & pos(c)) | (neg(b) & pos(c))) != 0;
}
template<typename T> inline bool addOverflow(T a, T b, T c)
{
	return ((neg(a) & neg(b) & pos(c)) | (pos(a) & pos(b) & neg(c))) != 0;
}
template<typename T> inline bool subCarry(T a, T b, T c)
{
	return ((neg(a) & pos(b)) | (neg(a) & pos(c)) | (pos(b) & pos(c))) != 0;
}
template<typename T> inline bool subOverflow(T a, T b, T c)
{
	return ((neg(a) & pos(b) & pos(c)) | (pos(a) & neg(b) & neg(c))) != 0;
}
}

#endif // FLAGHELPERS_H
