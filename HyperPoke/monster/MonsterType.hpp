#pragma once

#include <string>

class MonsterType
{
public:
	enum class Type
	{
		Normal,
		Fighting,
		Flying,
		Poison,
		Ground,
		Rock,
		Bug,
		Ghost,
		Steel,
		Mystery,
		Fire,
		Water,
		Grass,
		Electric,
		Psychic,
		Ice,
		Dragon,
		Dark,

		// keep last
		TypeCount,
	};
private:

};

std::string to_string(MonsterType::Type type);