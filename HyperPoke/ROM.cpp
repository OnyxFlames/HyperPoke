#include "ROM.hpp"

#include <iostream>
#include <fstream>

#include "Text.hpp"
#include "OffsetTable.hpp"
#include "Common.hpp"

ROM::ROM()
{
}

ROM::ROM(const std::string& name)
{
	loadFromFile(name);
}

void ROM::writeToFile(const std::string& name)
{
	std::ofstream output(name, std::ios::binary);

	output.write((char*)data.data(), data.size());
}

bool ROM::loadFromFile(const std::string& name)
{
	if (data.size() > 0)
		data.clear();
	std::ifstream input(name, std::ios::binary);

	if (!input.is_open())
	{
		std::cerr << "Failed to open file '" << name << "'";
		return false;
	}
	input.seekg(0, input.end);
	size_t size = static_cast<size_t>(input.tellg());
	input.seekg(0, input.beg);
	data.resize(size);
	input.read((char*)&data[0], size);

	mType = decodeRomType(data.data() + 0xac);

	return true;
}

RomType ROM::getType() const
{
	return mType;
}
