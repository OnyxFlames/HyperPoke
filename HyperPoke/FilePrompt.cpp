#include "FilePrompt.hpp"

#include <Windows.h>

std::string FilePrompt::getFilePrompt(std::string title, std::string filter)
{

	const int max_size = 1024;
	char filename[max_size];
	OPENFILENAME ofn;
	std::memset(filename, 0, max_size);
	std::memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = filter.c_str();
	ofn.lpstrFile = filename;
	ofn.nMaxFile = max_size;
	ofn.lpstrTitle = title.c_str();

	if (GetOpenFileName(&ofn))
		return std::string(filename);
	else
		return std::string();
}
