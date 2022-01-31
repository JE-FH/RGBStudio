#pragma once
#include <string>
#include <vector>

class EncodingConverter {
public:
	static std::u16string utf8_to_utf16(const std::string& target);
	static std::u16string utf8_to_utf16(const std::vector<char>& target);
};
