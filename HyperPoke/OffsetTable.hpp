#pragma once

#include "RomType.hpp"

#include <cstdint>

class OffsetTable
{
private:
	ROMType mType;
public:
	OffsetTable(ROMType type);

	uint32_t getMonsterNameOffset();
	uint32_t getBaseStatOffset();
	uint32_t getMoveDataOffset();
	uint32_t getMoveNameOffset();
	uint32_t getTypeNameOffset();
	uint32_t getItemOffset();
	uint32_t getMonsterFrontSpriteOffset();
	uint32_t getMonsterNormalPallet();
};

