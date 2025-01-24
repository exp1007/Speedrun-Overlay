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

	while (true) {

		uint32_t playerMovePtr;
		SDK::playermove_s playerMove;

		Memory::ReadMemory(Process::ClientModuleBase + offsets::GlobalPtr_playermove_s, &playerMovePtr);
		Memory::ReadMemory(playerMovePtr, &playerMove);

		gameData.playerGroundSpeed = std::sqrt(playerMove.velocity.x * playerMove.velocity.x + playerMove.velocity.y * playerMove.velocity.y);
		gameData.fps = 1.f / playerMove.frametime;

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
		//printf("fps: %f\n", simulatedFps);

		//for (int index = 0; index < 150; index++) {
		//	if(physEnt[index].team != 0)
		//		printf("(%d) team: %d\n", index, physEnt[index].team);
		//	if (physEnt[index].solid != 0)
		//		printf("(%d) solid: %d\n", index, physEnt[index].solid);
		//	if (physEnt[index].takedamage != 0)
		//		printf("(%d) takedamage: %d\n", index, physEnt[index].takedamage);
		//}
		//printf("Frametime: %f (%f)\n", playerMove.frametime, gameData.fps);
		//printf("Speed: %.2f, %.2f, %.2f\n", playerMove.velocity.x, playerMove.velocity.y, playerMove.velocity.z);
		//printf("Origin: %.2f, %.2f, %.2f\n", playerMove.origin.x, playerMove.origin.y, playerMove.origin.z);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}
