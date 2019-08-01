#include "Utils.h"
#include <fstream> 

bool Utils::fileExists(const char* path)
{
	std::ifstream ifile(path);
	return ifile.is_open();
}
