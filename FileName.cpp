#include "FileName.h"
#include <sstream>

std::string mygetFileName()
{
	++id;
	std::ostringstream oss;
	oss << "output" << id << ".bmp";
	return oss.str();
}
