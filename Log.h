#ifndef LOG_H
#define LOG_H

#include <ostream>

namespace Log
{
enum class Type
{
	INFO,
	WARNING,
	ERROR,
	DEBUG
};

std::ostream &message(Type type);

inline std::ostream &info() { return message(Type::INFO); }
inline std::ostream &warning() { return message(Type::WARNING); }
inline std::ostream &error() { return message(Type::ERROR); }
inline std::ostream &debug() { return message(Type::DEBUG); }
}

#endif // LOG_H
