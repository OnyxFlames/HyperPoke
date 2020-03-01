#pragma once

#include "RomType.hpp"

#include <cstdint>

class OffsetTable
{
private:
	RomType mType;
public:
	OffsetTable(RomType type);

	uint32_t getMonsterNameOffset();
	uint32_t getBaseStatOffset();
	uint32_t getMoveDataOffset();
	uint32_t getMoveNameOffset();
	uint32_t getTypeNameOffset();
};

