#include "MonsterBaseStats.hpp"

#include <fstream>

#include "../ROM.hpp"
#include "../OffsetTable.hpp"

#include "../Common.hpp"

#include "../Memory.hpp"

void MonsterBaseStats::load(uint8_t* data)
{
	base_HP = seq_read<uint8_t>(data);
	base_attack = seq_read<uint8_t>(data);
	base_defense = seq_read<uint8_t>(data);
	base_speed = seq_read<uint8_t>(data);
	base_spattack = seq_read<uint8_t>(data);
	base_spdefense = seq_read<uint8_t>(data);
	type1 = seq_read<uint8_t>(data);
	type2 = seq_read<uint8_t>(data);
	catch_rate = seq_read<uint8_t>(data);
	base_xp_yield = seq_read<uint8_t>(data);
	effort_yield.total = seq_read<uint16_t>(data);
	item1 = seq_read<uint16_t>(data);
	item2 = seq_read<uint16_t>(data);
	gender = seq_read<uint8_t>(data);
	egg_cycles = seq_read<uint8_t>(data);
	base_friendship = seq_read<uint8_t>(data);
	levelup_type = seq_read<uint8_t>(data);
	egg_group1 = seq_read<uint8_t>(data);
	egg_group2 = seq_read<uint8_t>(data);
	ability1 = seq_read<uint8_t>(data);
	ability2 = seq_read<uint8_t>(data);
	safarizone_rate = seq_read<uint8_t>(data);
	colorflip = seq_read<uint8_t>(data);
	padding_0 = seq_read<uint16_t>(data);
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

MonsterBaseStats::MonsterBaseStats(uint8_t* data)
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
