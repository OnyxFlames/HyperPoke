#pragma once

#include <string>
#include <vector>
#include "../Common.hpp"

#include "../ROM.hpp"

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

public:
	static std::vector<std::wstring> load(ROM& rom);
};

std::string to_string(MonsterType::Type type);