#pragma once
#include "../SDK/GameSDK.hpp"

struct GameDataStruct {
	float playerGroundSpeed;
	float fps;
	float timer;
};

extern GameDataStruct gameData;