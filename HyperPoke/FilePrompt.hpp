#pragma once

#include "Common.hpp"
#include <string>

class FilePrompt
{
public:
	static std::string getFilePrompt(std::string title, std::string filter);
};

