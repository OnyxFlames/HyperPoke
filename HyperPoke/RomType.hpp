#pragma once

#include <cstdint>
#include <cstring>
#include <string>

class ROM;

enum ROMType
{
	UNKNOWN_ROM,
	RUBY_US,
	SAPPHIRE_US,
	FIRERED_US,
	LEAFGREEN_US,
	EMERALD_US,
};

ROMType decodeRomType(const uint8_t* data);
ROMType decodeRomType(const ROM& rom);

bool isFRLGBase(ROMType type);
bool isRSEBase(ROMType type);

const std::string to_string(ROMType type);