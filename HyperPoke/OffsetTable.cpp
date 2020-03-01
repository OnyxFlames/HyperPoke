#include "OffsetTable.hpp"

OffsetTable::OffsetTable(RomType type)
	:	mType(type)
{
}

uint32_t OffsetTable::getMonsterNameOffset()
{
	switch (mType)
	{
	case RomType::EMERALD_US: return 0x3185C8;
	case RomType::FIRERED_US: return 0x245EE0;
	default: return 0;
	}
}

uint32_t OffsetTable::getBaseStatOffset()
{
	switch (mType)
	{
	case RomType::EMERALD_US: return 0x3203CC;
	case RomType::FIRERED_US: return 0x254784;
	default: return 0;
	}
}

uint32_t OffsetTable::getMoveDataOffset()
{
	switch (mType)
	{
	case RomType::EMERALD_US: return 0x32937C;
	case RomType::FIRERED_US: return 0x25D7B4;
	default: return 0;
	}
}

uint32_t OffsetTable::getMoveNameOffset()
{
	switch (mType)
	{
	case RomType::EMERALD_US: return 0x31977C;
	case RomType::FIRERED_US: return 0x247094;
	default: return 0;
	}
}

uint32_t OffsetTable::getTypeNameOffset()
{
	switch (mType)
	{
	case RomType::FIRERED_US: return 0x24f1a0;
	}
}
