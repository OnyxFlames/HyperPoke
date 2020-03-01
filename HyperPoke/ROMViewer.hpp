#pragma once

#include "Common.hpp"

#include "ROM.hpp"
#include "monster/MonsterBaseStats.hpp"
#include "monster/MonsterEvolutionData.hpp"
#include "monster/MonsterMoveData.hpp"

class ROMViewer
{
private:
	ROM& mROM;
	RomType mType;
public:
	ROMViewer(ROM& rom);

	const std::wstring readMonsterName(size_t index);
	bool writeMonsterName(size_t index, const std::wstring name);

	const std::wstring readMoveName(size_t index);
	bool writeMoveName(size_t index, const std::wstring name);

	const MonsterBaseStats readMonsterStats(size_t index);
	bool writeMonsterStats(size_t index, const MonsterBaseStats& stats);
};

