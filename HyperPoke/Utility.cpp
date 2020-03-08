#include "Utility.hpp"

#include "Text.hpp"
#include <sstream>
#include <iomanip>
#include <cctype>

template<typename T> 
T trim_whitespace(const T& str)
{
	T ret = T();
	for (const auto c : str)
		if (!std::isspace(c))
			ret += c;

	return ret;
}

std::wstring ByteArrayToByteString(std::vector<uint8_t> arr)
{
	std::wstringstream ss;
	for (auto c : arr)
	{
		ss << std::setw(2) << std::setfill(L'0') << std::hex << static_cast<uint16_t>(c);
	}

	return ss.str();
}

std::vector<uint8_t> ByteStringToByteArray(std::wstring str)
{
	str = trim_whitespace(str);
	std::wstring buff;
	std::vector<uint8_t> res;
	for (size_t i = 0; i < str.size(); i += 2, buff = L"")
	{
		buff += str[i];

		if (i + 1 < str.size())
			buff += str[i + 1];

		res.push_back(static_cast<uint8_t>(std::stoi(buff, nullptr, 16)));
	}
	if (res.size() > 0)
	{
		if (res.back() != 0xff)
			res.push_back(0xff);
	}

	return res;
}
