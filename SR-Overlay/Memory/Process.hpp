#pragma once

namespace Process {
	extern DWORD ProcID;
	extern HANDLE ProcHandle;
	extern uintptr_t ClientModuleBase;
	extern uintptr_t RenderingModuleBase;

	void SetupProcess();
}