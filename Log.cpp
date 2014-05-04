#include "Log.h"

#include <iostream>

namespace Log
{
std::ostream &message(Type type)
{
	switch (type)
	{
	case Type::INFO    : std::cerr << "[Info]    "; break;
	case Type::WARNING : std::cerr << "[Warning] "; break;
	case Type::ERROR   : std::cerr << "[Error]   "; break;
	case Type::DEBUG   : std::cerr << "[Debug]   "; break;
	}
	return std::cerr;
}
}
