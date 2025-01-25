#include <thread>
#include <cmath>

#include "Memory.hpp"
#include "../Headers/Offsets.hpp"
#include "../Headers/GameData.hpp"
#include "../SDK/GameSDK.hpp"

#define MAX_FPS_ARRAY 50

GameDataStruct gameData;

void Memory::Loop() {
	float oldFps[MAX_FPS_ARRAY];
	int currentFpsIndex = 0;

	float prevServerTime = 0.f;

	uint32_t timerState = 0;
	uint32_t prevTimerState = 0;

	while (true) {

		uint32_t playerMovePtr;
		SDK::playermove_s playerMove;

		Memory::ReadMemory(Process::ClientModuleBase + offsets::GlobalPtr_playermove_s, &playerMovePtr);
		Memory::ReadMemory(playerMovePtr, &playerMove);

		// Ground speed
		gameData.playerGroundSpeed = std::sqrt(playerMove.velocity.x * playerMove.velocity.x + playerMove.velocity.y * playerMove.velocity.y);

		// Simulated FPS
		{
			oldFps[currentFpsIndex] = 1.f / playerMove.frametime;
			if (currentFpsIndex == MAX_FPS_ARRAY)
				currentFpsIndex = 0;
			else
				currentFpsIndex++;

			float simulatedFps = 0.f;
			for (uint32_t index = 0; index < MAX_FPS_ARRAY; index++) {
				simulatedFps += oldFps[index];
			}
			simulatedFps = simulatedFps / MAX_FPS_ARRAY;
			gameData.fps = simulatedFps;
		}

		// Timer
		{
			// Using iuser2 as communication chanel for server timer state
			timerState = playerMove.iuser2;

			if (timerState == SDK::in_finish)
				continue;

			if (timerState != prevTimerState) {
				prevTimerState = timerState;
				prevServerTime == 0;
				gameData.timer = 0.f;
			}

			if (prevServerTime == 0)
				prevServerTime = playerMove.server;

			gameData.timer += (playerMove.server - prevServerTime) / 1000;
			prevServerTime = playerMove.server;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
