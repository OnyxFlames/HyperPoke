#include "RomType.hpp"


ROMType decodeRomType(const uint8_t* data)
{

	if (std::memcmp("AXPE", data, 4) == 0)
		return SAPPHIRE_US;
	else if (std::memcmp("AXVE", data, 4) == 0)
		return RUBY_US;
	else if (std::memcmp("BPRE", data, 4) == 0)
		return FIRERED_US;
	else if (std::memcmp("BPGE", data, 4) == 0)
		return LEAFGREEN_US;
	else if (std::memcmp("BPEE", data, 4) == 0)
		return EMERALD_US;
	else
		return UNKNOWN_ROM;

}

#include "ROM.hpp"

ROMType decodeRomType(const ROM& rom)
{
	return decodeRomType(&rom.data[0xac]);
}

bool isFRLGBase(ROMType type)
{
	switch (type)
	{
	case FIRERED_US:
	case LEAFGREEN_US:
		return true;
	default: return false;
	}
}

bool isRSEBase(ROMType type)
{
	switch (type)
	{
	case RUBY_US:
	case SAPPHIRE_US:
	case EMERALD_US:
		return true;
	default: return false;
	}
}

const std::string to_string(ROMType type)
{
	switch (type)
	{
	case SAPPHIRE_US: return "Sapphire (US)";
	case RUBY_US: return "Ruby (US)";
	case FIRERED_US: return "FireRed (US)";
	case LEAFGREEN_US: return "LeafGreen (US)";
	case EMERALD_US: return "Emerald (US)";
	default: return "Unknown ROM";
	}
}
