#pragma once

#include "../Common.hpp"

class MonsterEvolutionData
{
private:

public:
	MonsterEvolutionData(const uint8_t* data);

private:
	void load(const int8_t* data);
};

