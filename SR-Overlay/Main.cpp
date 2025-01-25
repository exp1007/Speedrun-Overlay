#include <thread>
#include <Windows.h>

#include "../UI/UI.hpp"
#include "../Memory/Process.hpp"
#include "../Memory/Memory.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// Setting process timers to update every 1 ms for better synchronization
	timeBeginPeriod(1);

#ifdef _DEBUG
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
#endif // _DEBUG

	Process::SetupProcess();

	std::thread memoryThread(Memory::Loop);
	memoryThread.detach();

	std::thread uiThread(UI::CreateOverlay);
	uiThread.join();

	return 0;
}