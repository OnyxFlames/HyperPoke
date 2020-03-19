#include "MonsterEggGroup.hpp"

std::string toMonsterEggGroup(uint8_t val)
{
	// TODO: See if egg group names are stored in ROM
	switch (val)
	{
	case 0: return "Invalid Egg Group";
	case 1: return "Monster";
	case 2: return "Water 1";
	case 3: return "Bug";
	case 4: return "Flying";
	case 5: return "Field";
	case 6: return "Fairy";
	case 7: return "Grass";
	case 8: return "Human-Like";
	case 9: return "Water 3";
	case 10: return "Mineral";
	case 11: return "Amorphous";
	case 12: return "Water 2";
	case 13: return "Ditto";
	case 14: return "Dragon";
	case 15: return "Undiscovered";

	default: return "Error Egg Group";
	}
}
