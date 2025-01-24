#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace UI {
	extern RECT clientSize;
	extern HWND clientHwnd;
	extern WINDOWINFO clientWindowInfo;

	int CreateOverlay();
	void ShowElements(bool* isMenuOpen);
}