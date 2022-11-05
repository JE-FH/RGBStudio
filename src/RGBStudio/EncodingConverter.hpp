#pragma once
#include <string>
#include <vector>

class EncodingConverter {
public:
	static std::u16string utf8_to_utf16(const std::string& target);
	static std::u16string utf8_to_utf16(const std::vector<char>& target);
	static std::string utf16_to_utf8(const std::wstring& target);
};
