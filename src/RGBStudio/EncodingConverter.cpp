#include "EncodingConverter.hpp"
#include <codecvt>

std::u16string EncodingConverter::utf8_to_utf16(const std::string& target) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
	return utf16conv.from_bytes(target);
}

std::u16string EncodingConverter::utf8_to_utf16(const std::vector<char>& target) {
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
	return utf16conv.from_bytes(target.begin()._Ptr, target.end()._Ptr);
}

std::string EncodingConverter::utf16_to_utf8(const std::wstring& target)
{
	throw std::runtime_error("Not yet implemented");
}
