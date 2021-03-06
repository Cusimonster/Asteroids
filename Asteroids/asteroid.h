#ifndef _ASTEROID_H                 // Prevent multiple definitions if this 
#define _ASTEROID_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace asteroidNS
{
	const int WIDTH = 94;                   // image width
    const int HEIGHT = 74;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI;  // radians per second
    const float SPEED = 100;                // 10 pixels per second
    const float MASS = 300.0f;              // mass

	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   ASTEROID_START_FRAME = 0;      // ship starts at frame 0
	const int   ASTEROID_END_FRAME = 0;         // ship animation frames 0,1,2,3
	const float ASTEROID_ANIMATION_DELAY = 0.2f;    // time between frames
}


class Asteroid : public Entity
{
public:
    // constructor
    Asteroid();

    // inherited member functions
    void update(float frameTime);

private:
};




#endif