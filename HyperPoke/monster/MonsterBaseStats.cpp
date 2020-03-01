#include "MonsterBaseStats.hpp"

#include <fstream>

#include "../ROM.hpp"
#include "../OffsetTable.hpp"

#include "../Common.hpp"

void MonsterBaseStats::load(const uint8_t* data)
{
	base_HP = *data++;
	base_attack = *data++;
	base_defense = *data++;
	base_speed = *data++;
	base_spattack = *data++;
	base_spdefense = *data++;
	type1 = *data++;
	type2 = *data++;
	catch_rate = *data++;
	base_xp_yield = *data++;
	effort_yield.total = (*data++);
	effort_yield.total += (*data++) << 8;
	item1 = (*data++); item1 += (*data++ << 8);
	item2 = (*data++); item2 += (*data++ << 8);
	gender = *data++;
	egg_cycles = *data++;
	base_friendship = *data++;
	levelup_type = *data++;
	egg_group1 = *data++;
	egg_group2 = *data++;
	ability1 = *data++;
	ability2 = *data++;
	safarizone_rate = *data++;
	colorflip = *data++;
	padding_0 = ((*data++ << 8) | *data++);
}

MonsterBaseStats::MonsterBaseStats(const uint8_t* data)
{
	load(data);
}

std::vector<MonsterBaseStats> MonsterBaseStats::load(ROM& rom)
{
	std::vector<MonsterBaseStats> stats;
	stats.reserve(412);

	OffsetTable table(rom.getType());

	for (size_t i = 0; i < MONSTER_COUNT; ++i)
		stats.push_back(MonsterBaseStats(&rom.data[i * MONSTER_BASESTAT_LENGTH + table.getBaseStatOffset()]));

	return stats;
}
