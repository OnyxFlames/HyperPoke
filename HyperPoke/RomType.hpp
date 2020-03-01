#pragma once

#include <cstdint>
#include <cstring>
#include <string>

class ROM;

enum RomType
{
	UNKNOWN_ROM,
	RUBY_US,
	SAPPHIRE_US,
	FIRERED_US,
	LEAFGREEN_US,
	EMERALD_US,
};

RomType decodeRomType(const uint8_t* data);

RomType decodeRomType(const ROM& rom);

const std::string to_string(RomType type);