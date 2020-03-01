#include "MonsterType.hpp"

#include "../Text.hpp"

// Note: Un-hardcode this when you can custom load type values

std::string to_string(MonsterType::Type type)
{
	switch (type)
	{
	case MonsterType::Type::Normal: return "Normal";
	case MonsterType::Type::Fighting: return "Fighting";
	case MonsterType::Type::Flying: return "Flying";
	case MonsterType::Type::Poison: return "Poison";
	case MonsterType::Type::Ground: return "Ground";
	case MonsterType::Type::Rock: return "Rock";
	case MonsterType::Type::Bug: return "Bug";
	case MonsterType::Type::Ghost: return "Ghost";
	case MonsterType::Type::Steel: return "Steel";
	case MonsterType::Type::Mystery: return "???";
	case MonsterType::Type::Fire: return "Fire";
	case MonsterType::Type::Water: return "Water";
	case MonsterType::Type::Grass: return "Grass";
	case MonsterType::Type::Electric: return "Electric";
	case MonsterType::Type::Psychic: return "Psychic";
	case MonsterType::Type::Ice: return "Ice";
	case MonsterType::Type::Dragon: return "Dragon";
	case MonsterType::Type::Dark: return "Dark";
	default: return "ErrorMonsterType";
	}
}

std::vector<std::wstring> MonsterType::load(ROM& rom)
{
	std::vector<std::wstring> names;

	OffsetTable table(rom.getType());
	const auto offset = table.getTypeNameOffset();
	auto data = rom.data.data();

	for (size_t i = 0; i <= TYPE_COUNT; ++i)
	{
		names.push_back(Text<std::wstring>::decode(data + offset + (i * TYPE_NAME_LENGTH)));
	}
	return names;
}
