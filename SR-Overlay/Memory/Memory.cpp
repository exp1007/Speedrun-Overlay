#include <thread>
#include <cmath>

#include "Memory.hpp"
#include "../Headers/Offsets.hpp"
#include "../Headers/GameData.hpp"
#include "../SDK/GameSDK.hpp"

GameDataStruct gameData;

void Memory::Loop() {
	while (true) {

		uint32_t playerMovePtr;
		SDK::playermove_s playerMove;

		Memory::ReadMemory(Process::ClientModuleBase + offsets::GlobalPtr_playermove_s, &playerMovePtr);
		Memory::ReadMemory(playerMovePtr, &playerMove);

		gameData.playerGroundSpeed = std::sqrt(playerMove.velocity.x * playerMove.velocity.x + playerMove.velocity.y * playerMove.velocity.y);
		gameData.fps = 1.f / playerMove.frametime;

		//printf("Frametime: %f (%f)\n", playerMove.frametime, gameData.fps);
		//printf("Speed: %.2f, %.2f, %.2f\n", playerMove.velocity.x, playerMove.velocity.y, playerMove.velocity.z);

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}
