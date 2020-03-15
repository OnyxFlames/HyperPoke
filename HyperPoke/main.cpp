
#include "monster/MonsterBaseStats.hpp"

#include <iostream>

#include "Application.hpp"
#include "Text.hpp"
#include "TextConversionTable.hpp"
#include <iomanip>
#include <fstream>

int main(int argc, char* argv[])
{
#if 0
	std::wofstream output("output.txt");
	for (int i = 0; i < 256; ++i)
	{
		if (i % 8 == 0 && i != 0)
			output << L"\n";
		if (DecodeTable[i] != L" " && i != 0)
			output << L"{ L\"" << DecodeTable[i] << L"\", 0x" << std::hex << std::setw(2) << std::setfill(L'0') << i << L" }, ";
		if (!output.good())
		{
			printf("Write failed\n");
			break;
		}
	}
#elif 0




#endif

	Application app;
	app.run();

	return 0;
}