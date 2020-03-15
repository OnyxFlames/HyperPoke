#include "LZ77.hpp"

std::vector<uint8_t> LZ77::decompress(const uint8_t* data, size_t size)
{
	std::vector<uint8_t> ret;

	if (size == 0)
		return ret;

	// Not compressed data
	if (data[0] != 0x10)
		return ret;

	size_t output_size = 0;

	output_size =
			((data[1] << 16))
		|	((data[2] <<  8))
		|	((data[3] <<  0));

	printf("Output size: %d\n", output_size);

	for (size_t i = 4; i < size; ++i)
	{

	}
}


