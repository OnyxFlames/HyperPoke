#pragma once


#include "Common.hpp"
#include <string>
#include <vector>
#include <cstdint>

#include "TextConversionTable.hpp"

template<typename T>
class Text
{
public:
	static std::vector<uint8_t> encode(const T& str);
	static T decode(uint8_t* data);
	static T decode(uint8_t* data, size_t amount);
};

template<typename T>
std::vector<uint8_t> Text<T>::encode(const T& str)
{
	T buff;
	std::vector<uint8_t> text;
#define add(x) text.push_back(x)
#define valid(x) (EncodeTable.find(x) != EncodeTable.end())
	const size_t size = str.size();

	for (size_t i = 0; i < size; ++i)
	{
		buff += str[i];
		if (valid(buff))
		{
			text.push_back(EncodeTable.find(buff)->second);
			buff = T();
		}
		else if (buff.size() >= 3)
			buff = T();

	}
	return text;
#undef add
#undef valid
}
template<typename T>
T Text<T>::decode(uint8_t* data)
{
	T text;

	for (; *data != 0xff; data++)
		text += DecodeTable[*data];

	return text;
}

template<typename T>
T Text<T>::decode(uint8_t* data, size_t amount)
{
	T text;

	for (size_t i = 0; *data != 0xff && i < amount; data++, ++i)
		text += DecodeTable[*data];

	return text;
}