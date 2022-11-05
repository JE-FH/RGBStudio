#pragma once
#include <windows.h>

class Win32Error : public std::exception {
	std::string error_message;
public:
	HRESULT result;
	Win32Error(HRESULT result);

	const char* what() const override;
};