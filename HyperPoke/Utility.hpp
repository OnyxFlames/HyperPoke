#pragma once

#include <vector>
#include <string>

std::wstring ByteArrayToByteString(std::vector<uint8_t> arr);
std::vector<uint8_t> ByteStringToByteArray(std::wstring str);

