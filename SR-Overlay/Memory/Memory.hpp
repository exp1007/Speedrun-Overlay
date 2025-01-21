#pragma once
#include <Windows.h>
#include "Process.hpp"

namespace Memory {
	void Loop();

    template <typename T>
    size_t ReadMemory(uintptr_t targetAddress, T* buffer, size_t bufferSize = sizeof(T)) {
        size_t bytesRead = 0;
        if (ReadProcessMemory(Process::ProcHandle, reinterpret_cast<LPCVOID>(targetAddress), buffer, bufferSize, &bytesRead)) {
            return bytesRead;
        }
        return 0;
    }
}

