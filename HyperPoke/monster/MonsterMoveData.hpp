#pragma once

#include "../Common.hpp"
#include <vector>

#include "../ROM.hpp"

enum AffectedMonster : uint8_t
{
	SelectedTarget =	0 << 0,
	DependsOnAttack =	1 << 0,
	Unused =			1 << 1,
	RandomTarget =		1 << 2,
	BothFoes =			1 << 3,
	User =				1 << 4,
	BothFoesAndUser =	1 << 5,
	OpponentField =		1 << 6,
};

enum MoveFlags : uint8_t
{
	MakesContact =		1 << 0,
	ProtectAffected =	1 << 1,
	MagicCoatAffected =	1 << 2,
	SnatchAffected =	1 << 3,
	MirrorMovable =		1 << 4,
	KingsRockAffected =	1 << 5,
};

class MonsterMoveData
{
private:
	uint8_t effect;
	uint8_t base_power;
	uint8_t type;
	uint8_t accuracy;
	uint8_t powerpoints;
	uint8_t effect_accuracy;
	AffectedMonster affects;
	uint8_t priority;
	MoveFlags flags;
	uint16_t padding_0;
	uint8_t  padding_1;
public:
	MonsterMoveData(const uint8_t* data);

	static std::vector<MonsterMoveData> load(ROM& rom);
private:
	void load(const uint8_t* data);
};

