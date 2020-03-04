#pragma once

#include "../Common.hpp"

#include <string>

enum MonsterGender
{
	AlwaysMale,
	MixedGender,
	AlwaysFemale,
	Genderless,

	GenderCount,
};

MonsterGender decodeGender(uint8_t val);
float genderRatioMale(uint8_t val);
float genderRatioFemale(uint8_t val);
const std::string to_string(MonsterGender gender);