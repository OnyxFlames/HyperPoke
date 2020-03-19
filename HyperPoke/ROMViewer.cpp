#include "ROMViewer.hpp"

#include "Text.hpp"

ROMViewer::ROMViewer(ROM& rom)
	:	mROM(rom)
	,	mType(rom.getType())
{
}

const std::wstring ROMViewer::readMonsterName(size_t index)
{
	std::wstring name = L"";

	if (mType == ROMType::UNKNOWN_ROM || index >= MONSTER_COUNT)
		return name;

	OffsetTable table(mType);
	const auto offset = table.getMonsterNameOffset();

	name = Text<std::wstring>::decode(&mROM.data[index * MONSTER_NAME_LENGTH + offset], MONSTER_NAME_LENGTH);

	return name;
}

bool ROMViewer::writeMonsterName(size_t index, const std::wstring& name)
{
	if (mType == ROMType::UNKNOWN_ROM || index > MONSTER_COUNT)
		return false;

#define NAME_INDEX ((index * MONSTER_NAME_LENGTH) + offset)
	if (name.size() > MONSTER_NAME_LENGTH)
		return false;

	auto bytes = Text<std::wstring>::encode(name);

	OffsetTable table(mType);
	const auto offset = table.getMonsterNameOffset();

	// do we need to write the terminator byte?
	if (bytes.size() < 11)
		mROM.data[NAME_INDEX + bytes.size()] = 0xFF;

	for (size_t i = 0; i < bytes.size(); ++i)
		mROM.data[NAME_INDEX + i] = bytes[i];

	return true;

#undef NAME_INDEX
}

const std::wstring ROMViewer::readMoveName(size_t index)
{
	std::wstring name = L"";

	if (mType == ROMType::UNKNOWN_ROM || index >= MOVE_COUNT)
		return name;

	OffsetTable table(mType);
	const auto offset = table.getMoveNameOffset();

	name = Text<std::wstring>::decode(&mROM.data[index * MOVE_NAME_LENGTH + offset], MOVE_NAME_LENGTH);

	return name;
}

bool ROMViewer::writeMoveName(size_t index, const std::wstring& name)
{
	if (mType == ROMType::UNKNOWN_ROM || index >= MOVE_COUNT)
		return false;

#define NAME_INDEX ((index * MOVE_NAME_LENGTH) + offset)
	if (name.size() > MOVE_NAME_LENGTH)
		return false;

	auto bytes = Text<std::wstring>::encode(name);

	OffsetTable table(mType);
	const auto offset = table.getMoveNameOffset();

	// do we need to write the terminator byte?
	if (bytes.size() < MOVE_NAME_LENGTH)
		mROM.data[NAME_INDEX + bytes.size()] = 0xFF;

	for (size_t i = 0; i < bytes.size(); ++i)
		mROM.data[NAME_INDEX + i] = bytes[i];

	return true;

#undef NAME_INDEX
}

const MonsterBaseStats ROMViewer::readMonsterStats(size_t index)
{
#define STAT_INDEX ((index * MONSTER_BASESTAT_LENGTH) + offset)

	OffsetTable table(mType);
	const auto offset = table.getBaseStatOffset();
	if (offset == 0)
		return MonsterBaseStats();

	MonsterBaseStats mStats(&mROM.data[STAT_INDEX]);

	return mStats;
}

#include "Memory.hpp"

bool ROMViewer::writeMonsterStats(size_t index, const MonsterBaseStats& stats)
{
#define STAT_INDEX ((index * MONSTER_BASESTAT_LENGTH) + offset)

	if (index > MONSTER_COUNT)
		return false;

	OffsetTable table(mType);
	const auto offset = table.getBaseStatOffset();
	if (offset == 0) return false;

	auto data = mROM.data.data() + STAT_INDEX;
	
	seq_write<uint8_t>(data, stats.base_HP);
	seq_write<uint8_t>(data, stats.base_attack);
	seq_write<uint8_t>(data, stats.base_defense);
	seq_write<uint8_t>(data, stats.base_speed);
	seq_write<uint8_t>(data, stats.base_spattack);
	seq_write<uint8_t>(data, stats.base_spdefense);

	seq_write<uint8_t>(data, stats.type1);
	seq_write<uint8_t>(data, stats.type2);

	seq_write<uint8_t>(data, stats.catch_rate);
	seq_write<uint8_t>(data, stats.base_xp_yield);

	seq_write<uint16_t>(data, stats.effort_yield.total);

	seq_write<uint16_t>(data, stats.item1);
	seq_write<uint16_t>(data, stats.item2);

	seq_write<uint8_t>(data, stats.gender);

	seq_write<uint8_t>(data, stats.egg_cycles);
	seq_write<uint8_t>(data, stats.base_friendship);
	seq_write<uint8_t>(data, stats.levelup_type);

	seq_write<uint8_t>(data, stats.egg_group1);
	seq_write<uint8_t>(data, stats.egg_group2);
	return true;
	seq_write<uint8_t>(data, stats.ability1);
	seq_write<uint8_t>(data, stats.ability2);

	seq_write<uint8_t>(data, stats.safarizone_rate);
	seq_write<uint8_t>(data, stats.colorflip);

	seq_write<uint16_t>(data, stats.padding_0);

	return true;
}

const std::wstring ROMViewer::readTypeName(size_t index)
{
	if (index > TYPE_COUNT || mType == ROMType::UNKNOWN_ROM)
		return L"";

	OffsetTable table(mType);
	const auto offset = table.getTypeNameOffset();
	if (offset == 0) return std::wstring();
	auto data = mROM.data.data();
	return Text<std::wstring>::decode(&data[index * TYPE_NAME_LENGTH + offset], TYPE_NAME_LENGTH);
}

bool ROMViewer::writeTypeName(size_t index, const std::wstring& name)
{
#define TYPE_INDEX ((index * TYPE_NAME_LENGTH) + offset)

	auto bytes = Text<std::wstring>::encode(name);
	if (bytes.size() > TYPE_NAME_LENGTH || index > TYPE_COUNT || mType == ROMType::UNKNOWN_ROM)
		return false;

	OffsetTable table(mType);
	const auto offset = table.getTypeNameOffset();
	if (offset == 0) return false;
	auto data = mROM.data.data();

	if (bytes.size() < TYPE_NAME_LENGTH)
		data[TYPE_INDEX + bytes.size()] = 0xff;

	for (size_t i = 0; i < bytes.size(); ++i)
		data[TYPE_INDEX + i] = bytes[i];

	return true;
}

const std::wstring ROMViewer::readItemName(size_t index)
{
#define ITEM_INDEX ((index * ITEM_DATA_LENGTH) + offset)

	OffsetTable table(mType);
	const auto offset = table.getItemOffset();
	if (offset == 0)
		return L"";

	return Text<std::wstring>::decode(&mROM.data[ITEM_INDEX], ITEM_NAME_LENGTH);

}

bool ROMViewer::writeItemName(size_t index, const std::wstring& name)
{
#define ITEM_INDEX ((index * ITEM_DATA_LENGTH) + offset)
	auto bytes = Text<std::wstring>::encode(name);

	if (bytes.size() > ITEM_NAME_LENGTH)
		return false;
	if ((	index > ITEM_COUNT_FRLG && isFRLGBase(mType))
		|| (index > ITEM_COUNT_RSE && isRSEBase(mType)))
			return false;

	OffsetTable table(mType);
	const auto offset = table.getItemOffset();

	auto data = mROM.data.data() + ITEM_INDEX;

	if (bytes.size() < ITEM_NAME_LENGTH)
		data[bytes.size()] = 0xff;

	for (size_t i = 0; i < bytes.size(); ++i)
		data[i] = bytes[i];

	return true;
}
