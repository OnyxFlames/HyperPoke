#pragma once

#include "Common.hpp"
#include <vector>
#include <string>

class LZ77
{
private:

public:
	static std::vector<uint8_t> decompress(const uint8_t* data, size_t size);


};

