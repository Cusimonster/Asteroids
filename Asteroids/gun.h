#ifndef _GUN_H                 // Prevent multiple definitions if this 
#define _GUN_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace gunNS
{
	const int WIDTH = 96;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	const float SCALE = 0.5;
    const float ROTATION_RATE = (float)PI;  // radians per second
    const float SPEED = 100;                // 10 pixels per second
    const float MASS = 300.0f;              // mass

	const int   TEXTURE_COLS = 1;           // texture has 2 columns
	const int   GUN_START_FRAME = 0;      // ship starts at frame 0
	const int   GUN_END_FRAME = 0;         // ship animation frames 0,1,2,3
	const float GUN_ANIMATION_DELAY = 0.2f;    // time between frames
}


class Gun : public Entity
{
protected:
	float shootTime;
public:
    // constructor
    Gun();

    // inherited member functions
    void update(float frameTime, bool& shoot);
};




#endif