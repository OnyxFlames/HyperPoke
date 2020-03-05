#include "MonsterGender.hpp"

MonsterGender decodeGender(uint8_t val)
{
	switch (val)
	{
	case 0:		return AlwaysMale;
	case 254:	return AlwaysFemale;
	case 255:	return Genderless;
	default:	return MixedGender;
	}
}
// TODO: math
float genderRatioMale(uint8_t val)
{
	MonsterGender gen = decodeGender(val);
	if (val == AlwaysMale)
		return 1.f;
	else if (gen != MixedGender)
		return val / 253.f;

	return 0.0f;
}

float genderRatioFemale(uint8_t val)
{
	MonsterGender gen = decodeGender(val);
	if (gen == AlwaysFemale)
		return 1.f;
	else if (gen != MixedGender)
		return 0.f;
	return 0.0f;
}

const std::string to_string(MonsterGender gender)
{
	switch (gender)
	{
	case AlwaysMale:	return "Male";
	case AlwaysFemale:	return "Female";
	case Genderless:	return "Genderless";
	case MixedGender:	return "Mixed";
	default: return "Invalid Gender";
	}
}
