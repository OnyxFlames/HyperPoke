#include "ColourPalette.hpp"

std::vector<sf::Color> getColourPalette(const uint8_t* data)
{
	std::vector<sf::Color> palette;


	uint16_t buff;

	uint8_t byte1, byte2;

	uint8_t red, green, blue;
	// https://github.com/Gamer2020/PokemonGameEditor/blob/aff8d33f332599c265410afd326d782fb977a69d/GBAPokemonGameEditor/GetImageFunctions.vb
	for (size_t i = 0; i < 0x1F; i += 2)
	{
		byte1 = data[i];
		byte2 = data[i + 1];
		buff = byte2 * 0x100 + byte1;

		red = (buff & 0x1F) * 0x8;
		green = (buff & 0x3E0) / 0x4;
		blue = (buff & 0x7C00) / 0x80;

		palette.push_back(sf::Color(red, green, blue));
	}

	return palette;
}
