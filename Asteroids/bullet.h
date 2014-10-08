#ifndef _BULLET_H                 // Prevent multiple definitions if this 
#define _BULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
	const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI;  // radians per second
    const float SPEED = 1000;                // 100 pixels per second
    const float MASS = 300.0f;              // mass

	const int   TEXTURE_COLS = 8;           // texture has 2 columns
	const int   BULLET_START_FRAME = 9;      // ship starts at frame 0
	const int   BULLET_END_FRAME = 9;         // ship animation frames 0,1,2,3
	const float BULLET_ANIMATION_DELAY = 0.2f;    // time between frames
}


class Bullet : public Entity
{
public:
    // constructor
    Bullet();

    // inherited member functions
    void update(float frameTime);
};




#endif