#include <thread>

#include "Memory.hpp"
#include "../Headers/Offsets.hpp"
#include "../Headers/GameData.hpp"

GameDataStruct gameData;

void Memory::Loop() {
	while (true) {

		Memory::ReadMemory(Process::ClientModuleBase + offsets::flSpeed, &gameData.flLocalSpeed);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
