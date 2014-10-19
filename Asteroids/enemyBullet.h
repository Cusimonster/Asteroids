#ifndef _ENEMY_BULLET_H                 // Prevent multiple definitions if this 
#define _ENEMY_BULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace enemyBulletNS
{
	const int WIDTH = 30;                   // image width
    const int HEIGHT = 18;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI;  // radians per second
    const float SPEED = 800;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
	const float SCALE = 0.3;			// image scale

	const int   TEXTURE_COLS = 1;           // texture has 2 columns
	const int   BULLET_START_FRAME = 0;      // ship starts at frame 0
	const int   BULLET_END_FRAME = 0;         // ship animation frames 0,1,2,3
	const float BULLET_ANIMATION_DELAY = 0.2f;    // time between frames
}


class EnemyBullet : public Entity
{
public:
    // constructor
    EnemyBullet();

    // inherited member functions
    void update(float frameTime);
};

#endif