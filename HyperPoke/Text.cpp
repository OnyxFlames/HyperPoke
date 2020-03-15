#include "Text.hpp"

#include <vector>
#include <iostream>
#include "TextConversionTable.hpp"

#include <fstream>
#include <iomanip>

bool instrinsic::generateDecodeTablePrototype(const char* filename)
{
	std::wofstream output(filename);
	for (int i = 0; i < 256; ++i)
	{
		if (i % 8 == 0 && i != 0)
			output << L"\n";
		if (DecodeTable[i] != L" " && i != 0)
			output << L"{ L\"" << DecodeTable[i] << L"\", 0x" << std::hex << std::setw(2) << std::setfill(L'0') << i << L" }, ";
		if (!output.good())
		{
			printf("Write failed\n");
			return false;
		}
	}
	return true;
}
