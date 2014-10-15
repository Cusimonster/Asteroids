#include "asteroid.h"

//extern int asteroidCounter = 0;
//extern int asterGroupSize = 1;

Asteroid::Asteroid() : Entity()
{
	spriteData.width = asteroidNS::WIDTH;           // size of Ship1
    spriteData.height = asteroidNS::HEIGHT;
    spriteData.x = asteroidNS::X;                   // location on screen
    spriteData.y = asteroidNS::Y;
    spriteData.rect.bottom = asteroidNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = asteroidNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    radius = asteroidNS::WIDTH/2.0 - 10;
    collisionType = entityNS::CIRCLE;
	active = false;
}


void Asteroid::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y;     // move ship along Y

	

	if (spriteData.x > GAME_WIDTH-asteroidNS::WIDTH*getScale() + 96)//NEC added + 96
    {
		setActive(false);
    }
    else if (spriteData.x < -96)//NEC changed from 0 to -96
    {
        setActive(false);
	}
    if (spriteData.y > GAME_HEIGHT-asteroidNS::HEIGHT*getScale() + 96)//NEC added + 96
    {
        setActive(false);
	}
	else if (spriteData.y < -96)//NEC changed from 0 to -96
	{
		setActive(false);
	}
}