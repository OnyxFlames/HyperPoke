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

MonsterBaseStats::MonsterBaseStats()
	:	base_HP(0)
	,	base_attack(0)
	,	base_defense(0)
	,	base_speed(0)
	,	base_spattack(0)
	,	base_spdefense(0)
	,	type1(0)
	,	type2(0)
	,	catch_rate(0)
	,	base_xp_yield(0)
	,	effort_yield(0)
	,	item1(0)
	,	item2(0)
	,	gender(0)
	,	egg_cycles(0)
	,	base_friendship(0)
	,	levelup_type(0)
	,	egg_group1(0)
	,	egg_group2(0)
	,	ability1(0)
	,	ability2(0)
	,	safarizone_rate(0)
	,	colorflip(0)
	,	padding_0(0)
{
}

MonsterBaseStats::MonsterBaseStats(const uint8_t* data)
{
	load(data);
}

std::vector<MonsterBaseStats> MonsterBaseStats::load(ROM& rom)
{
	std::vector<MonsterBaseStats> stats;
	stats.reserve(MONSTER_COUNT);

	OffsetTable table(rom.getType());

	for (size_t i = 0; i < MONSTER_COUNT; ++i)
		stats.push_back(MonsterBaseStats(&rom.data[i * MONSTER_BASESTAT_LENGTH + table.getBaseStatOffset()]));

	return stats;
}
