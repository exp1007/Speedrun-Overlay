#pragma once
#include <cstdint>

struct vec3_t {
	float x, y, z;
};

namespace SDK {

	// https://github.com/ValveSoftware/halflife/blob/b1b5cf5892918535619b2937bb927e46cb097ba1/pm_shared/pm_defs.h#L89

	struct playermove_s {
		uint8_t padding1[0x8];

		int				player_index;  // So we don't try to run the PM_CheckStuck nudging too quickly.
		bool			server;        // For debugging, are we running physics code on server side?

		bool			multiplayer;   // 1 == multiplayer server
		float			frametime;

		vec3_t			forward, right, up; // Vectors for angles

		// player state
		vec3_t			origin;        // Movement origin.
		vec3_t			angles;        // Movement view angles.
		vec3_t			oldangles;     // Angles before movement view angles were looked at.
		vec3_t			velocity;      // Current movement direction.
		vec3_t			movedir;       // For waterjumping, a forced forward velocity so we can fly over lip of ledge.
		vec3_t			basevelocity;  // Velocity of the conveyor we are standing, e.g.

		// For ducking/dead
		vec3_t			view_ofs;      // Our eye position.
		float			flDuckTime;    // Time we started duck
		bool			bInDuck;       // In process of ducking or ducked already?
	};
}