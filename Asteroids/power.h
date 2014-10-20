#ifndef _POWER_H                 // Prevent multiple definitions if this 
#define _POWER_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace powerNS
{
	const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI;  // radians per second
    const float SPEED = 150;                // 10 pixels per second
    const float MASS = 300.0f;              // mass
	const float SCALE = 0.8;

	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   POWER_START_FRAME = 0;      // ship starts at frame 0
	const int   POWER_END_FRAME = 0;         // ship animation frames 0,1,2,3
	const float POWER_ANIMATION_DELAY = 0.2f;    // time between frames
}

class Power : public Entity
{
public:
    // constructor
    Power();

    // inherited member functions
    void update(float frameTime);

private:
};

#endif