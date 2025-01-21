#pragma once

namespace Process {
	extern DWORD ProcID;
	extern HANDLE ProcHandle;
	extern uintptr_t ClientModuleBase;

	void SetupProcess();
}