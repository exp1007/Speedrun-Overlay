#pragma once
#include <Windows.h>
#include "Process.hpp"

namespace Memory {
	void Loop();

    template <typename T>
    SIZE_T ReadMemory(uintptr_t targetAddress, T* buffer, SIZE_T bufferSize = sizeof(T)) {
        SIZE_T bytesRead = 0;
        if (ReadProcessMemory(Process::ProcHandle, reinterpret_cast<LPCVOID>(targetAddress), buffer, bufferSize, &bytesRead)) {
            return bytesRead;
        }
        return 0;
    }
}

