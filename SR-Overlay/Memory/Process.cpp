#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <psapi.h>

#include "../UI/UI.hpp"
#include "../Memory/Process.hpp"

// Ensuring extern variables are declared before using
// ---------------------------------------------------
HWND UI::clientHwnd;
RECT UI::clientSize;
WINDOWINFO UI::clientWindowInfo;

DWORD Process::ProcID;
HANDLE Process::ProcHandle;
uintptr_t Process::ClientModuleBase;
uintptr_t Process::RenderingModuleBase;
// ---------------------------------------------------

DWORD FindProcessId(const std::string processName)
{
    PROCESSENTRY32 processInfo;
    processInfo.dwSize = sizeof(processInfo);

    HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (processesSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }

    Process32First(processesSnapshot, &processInfo);
    if (!processName.compare(processInfo.szExeFile))
    {
        CloseHandle(processesSnapshot);
        return processInfo.th32ProcessID;
    }

    while (Process32Next(processesSnapshot, &processInfo))
    {
        if (!processName.compare(processInfo.szExeFile))
        {
            CloseHandle(processesSnapshot);
            return processInfo.th32ProcessID;
        }
    }

    CloseHandle(processesSnapshot);
    return 0;
}

DWORD_PTR GetModuleBaseAddress(DWORD processID, const std::string& moduleName) {
    MODULEENTRY32 moduleEntry;
    moduleEntry.dwSize = sizeof(MODULEENTRY32);

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processID);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return 0;
    }
    if (Module32First(hSnapshot, &moduleEntry)) {
        do {
            if (moduleName == moduleEntry.szModule) {
                CloseHandle(hSnapshot);
                return (DWORD_PTR)moduleEntry.modBaseAddr;
            }
        } while (Module32Next(hSnapshot, &moduleEntry));
    }
    else
        return 0;

    CloseHandle(hSnapshot);
    return 0;
}

void Process::SetupProcess() {

    // Memory
    Process::ProcID = FindProcessId("hl.exe");
    Process::ProcHandle = OpenProcess(PROCESS_VM_READ | SYNCHRONIZE, FALSE, Process::ProcID);
    Process::ClientModuleBase = GetModuleBaseAddress(Process::ProcID, "client.dll");
    Process::RenderingModuleBase = GetModuleBaseAddress(Process::ProcID, "nvwgf2um.dll");

    // UI
	UI::clientHwnd = FindWindow(nullptr, "Counter-Strike");
	GetClientRect(UI::clientHwnd, &UI::clientSize);
    GetWindowInfo(UI::clientHwnd, &UI::clientWindowInfo);

}