#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "../ROM.hpp"

class MonsterBaseStats
{
private:
public:
	uint8_t base_HP;
	uint8_t base_attack;
	uint8_t base_defense;
	uint8_t base_speed;
	uint8_t base_spattack;
	uint8_t base_spdefense;
	uint8_t type1;
	uint8_t type2;
	uint8_t catch_rate;
	uint8_t base_xp_yield;
	//uint16_t effort_yield;
	union EffortYield
	{
		uint16_t total;
		struct
		{
			uint16_t HP : 2;
			uint16_t Attack : 2;
			uint16_t Defense : 2;
			uint16_t Speed : 2;
			uint16_t SpAttack : 2;
			uint16_t SpDefense : 2;

			uint16_t padding_0 : 2;
		};
		EffortYield() { }
		EffortYield(uint16_t y)
			:	total(y)
		{ }
	} effort_yield;

	uint16_t item1;
	uint16_t item2;
	uint8_t gender;
	uint8_t egg_cycles;
	uint8_t base_friendship;
	uint8_t levelup_type;
	uint8_t egg_group1;
	uint8_t egg_group2;
	uint8_t ability1;
	uint8_t ability2;
	uint8_t safarizone_rate;
	uint8_t colorflip;
	uint16_t padding_0;

public:
	MonsterBaseStats();
	MonsterBaseStats(uint8_t* data);

	static std::vector<MonsterBaseStats> load(ROM& rom);
private:
	void load(uint8_t* data);
};

