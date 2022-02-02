#pragma once
#include "Win32Error.hpp"
#include <windows.h>

template<typename Func>
class COMCallbackExceptionProtection {
public:
	COMCallbackExceptionProtection(Func func)
		: func(func)
	{}

	template<typename... Args>
	HRESULT operator()(Args &&... args) {
		try {
			func(std::forward<Args>(args)...);
			return S_OK;
		}
		catch (const Win32Error& err) {
			return err.result;
		}
		catch (const std::exception& err) {
			std::cout << err.what() << std::endl;
			return E_FAIL;
		}
		return E_FAIL;
	}

	static COMCallbackExceptionProtection decorate(Func func) {
		return COMCallbackExceptionProtection<Func>(std::move(func));
	}
private:
	Func func;
};