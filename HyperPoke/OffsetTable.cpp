#include "OffsetTable.hpp"

OffsetTable::OffsetTable(ROMType type)
	:	mType(type)
{
}

uint32_t OffsetTable::getMonsterNameOffset()
{
	switch (mType)
	{
	case ROMType::EMERALD_US: return 0x3185C8;
	case ROMType::FIRERED_US: return 0x245EE0;
	default: return 0;
	}
}

uint32_t OffsetTable::getBaseStatOffset()
{
	switch (mType)
	{
	case ROMType::EMERALD_US: return 0x3203CC;
	case ROMType::FIRERED_US: return 0x254784;
	default: return 0;
	}
}

uint32_t OffsetTable::getMoveDataOffset()
{
	switch (mType)
	{
	case ROMType::EMERALD_US: return 0x32937C;
	case ROMType::FIRERED_US: return 0x25D7B4;
	default: return 0;
	}
}

uint32_t OffsetTable::getMoveNameOffset()
{
	switch (mType)
	{
	case ROMType::EMERALD_US: return 0x31977C;
	case ROMType::FIRERED_US: return 0x247094;
	default: return 0;
	}
}

uint32_t OffsetTable::getTypeNameOffset()
{
	switch (mType)
	{
	case ROMType::FIRERED_US: return 0x24f1a0;
	case ROMType::EMERALD_US: return 0x31ae38;
	default: return 0;
	}
}

uint32_t OffsetTable::getItemOffset()
{
	switch (mType)
	{
	case ROMType::FIRERED_US: return 0x3DB028;
	case ROMType::EMERALD_US: return 0x5839A0;
	default: return 0;
	}
}

uint32_t OffsetTable::getMonsterFrontSpriteOffset()
{
	switch (mType)
	{
	case ROMType::FIRERED_US: return 0x2350AC;
	default: return 0;
	}
}

uint32_t OffsetTable::getMonsterNormalPallet()
{
	switch (mType)
	{
	case ROMType::FIRERED_US: return 0x23730C;
	default: return 0;
	}
}

uint32_t OffsetTable::getAbilityNameOffset()
{

	switch (mType)
	{
	case ROMType::FIRERED_US: return 0x24FC40;
	default: return 0;
	}

}
