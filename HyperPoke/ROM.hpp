#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "RomType.hpp"
#include "OffsetTable.hpp"


class ROM
{
private:
	ROMType mType;
public:
	ROM();
	ROM(const std::string& name);

	std::vector<uint8_t> data;

	void writeToFile(const std::string& name);
	bool loadFromFile(const std::string& name);
	ROMType getType() const;
};

