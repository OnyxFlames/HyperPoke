#include "MonsterMoveData.hpp"

#include "../OffsetTable.hpp"

MonsterMoveData::MonsterMoveData(const uint8_t* data)
{
	load(data);
}

std::vector<MonsterMoveData> MonsterMoveData::load(ROM& rom)
{
	OffsetTable table(rom.getType());
	std::vector<MonsterMoveData> moves;
	moves.reserve(354);

	for (size_t i = 0; i < 354; ++i)
		moves.push_back(MonsterMoveData(&rom.data[i * 12 + table.getMoveDataOffset()]));

	return moves;
}

void MonsterMoveData::load(const uint8_t* data)
{
	effect = *data++;
	base_power = *data++;
	type = *data++;
	accuracy = *data++;
	powerpoints = *data++;
	effect_accuracy = *data++;
	affects = (AffectedMonster)*data++;
	priority = *data++;
	flags = (MoveFlags)*data++;
}
