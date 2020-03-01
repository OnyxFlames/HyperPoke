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

	if (mType == RomType::UNKNOWN_ROM || index >= MONSTER_COUNT)
		return name;

	OffsetTable table(mType);
	const auto offset = table.getMonsterNameOffset();

	name = Text<std::wstring>::decode(&mROM.data[index * MONSTER_NAME_LENGTH + offset], MONSTER_NAME_LENGTH);

	return name;
}

bool ROMViewer::writeMonsterName(size_t index, const std::wstring& name)
{
	if (mType == RomType::UNKNOWN_ROM || index > MONSTER_COUNT)
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

	if (mType == RomType::UNKNOWN_ROM || index >= MOVE_COUNT)
		return name;

	OffsetTable table(mType);
	const auto offset = table.getMoveNameOffset();

	name = Text<std::wstring>::decode(&mROM.data[index * MOVE_NAME_LENGTH + offset], MOVE_NAME_LENGTH);

	return name;
}

bool ROMViewer::writeMoveName(size_t index, const std::wstring& name)
{
	if (mType == RomType::UNKNOWN_ROM || index >= MOVE_COUNT)
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

	MonsterBaseStats mStats(&mROM.data[STAT_INDEX]);

	return mStats;
}

bool ROMViewer::writeMonsterStats(size_t index, const MonsterBaseStats& stats)
{
#define STAT_INDEX ((index * MONSTER_BASESTAT_LENGTH) + offset)

	if (index > MONSTER_COUNT)
		return false;

	OffsetTable table(mType);
	const auto offset = table.getBaseStatOffset();

	auto data = mROM.data.data() + STAT_INDEX;

	data[0] = stats.base_HP;
	data[1] = stats.base_attack;
	data[2] = stats.base_defense;
	data[3] = stats.base_speed;
	data[4] = stats.base_spattack;
	data[5] = stats.base_spdefense;
	
	data[6] = stats.type1;
	data[7] = stats.type2;
// disable other data writing until menu supports it

	data[8] = stats.catch_rate;
	data[9] = stats.base_xp_yield;

	data[10] = stats.effort_yield.total & 0xFF;
	data[11] = (stats.effort_yield.total >> 8) & 0xFF;

	return true;

	data[12] = stats.item1 & 0xFF;
	data[13] = (stats.item1 >> 8) & 0xFF;

	data[14] = stats.item2 & 0xFF;
	data[15] = (stats.item2 >> 8) & 0xFF;

	data[16] = stats.gender;
	data[17] = stats.egg_cycles;
	data[18] = stats.base_friendship;
	data[19] = stats.levelup_type;
	data[20] = stats.egg_group1;
	data[21] = stats.egg_group2;
	data[22] = stats.ability1;
	data[23] = stats.ability2;
	data[24] = stats.safarizone_rate;
	data[25] = stats.colorflip;

	data[26] = stats.padding_0 & 0xFF;
	data[27] = (stats.padding_0 >> 8) & 0xFF;

	return true;
}

const std::wstring ROMViewer::readTypeName(size_t index)
{
	OffsetTable table(mType);
	const auto offset = table.getTypeNameOffset();
	auto data = mROM.data.data();
	return Text<std::wstring>::decode(&data[index * TYPE_NAME_LENGTH + offset], TYPE_NAME_LENGTH);
}

bool ROMViewer::writeTypeName(size_t index, const std::wstring& name)
{
	return false;
}
