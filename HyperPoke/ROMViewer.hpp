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
	ROMType mType;
public:
	ROMViewer(ROM& rom);

	const std::wstring readMonsterName(size_t index);
	bool writeMonsterName(size_t index, const std::wstring& name);

	const std::wstring readMoveName(size_t index);
	bool writeMoveName(size_t index, const std::wstring& name);

	const MonsterBaseStats readMonsterStats(size_t index);
	bool writeMonsterStats(size_t index, const MonsterBaseStats& stats);

	const std::wstring readTypeName(size_t index);
	bool writeTypeName(size_t index, const std::wstring& name);

	const std::wstring readItemName(size_t index);
	bool writeItemName(size_t index, const std::wstring& name);

	const std::wstring readMonsterAbility(size_t index);
	bool writeMonsterAbility(size_t index, const std::wstring& name);
};

