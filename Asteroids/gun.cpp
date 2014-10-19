#include "gun.h"

Gun::Gun() : Entity()
{
	spriteData.width = gunNS::WIDTH;           // size of Ship1
    spriteData.height = gunNS::HEIGHT;
    spriteData.x = gunNS::X;                   // location on screen
    spriteData.y = gunNS::Y;
    spriteData.rect.bottom = gunNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = gunNS::WIDTH;
	spriteData.scale = gunNS::SCALE;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    radius = gunNS::WIDTH/2.0 - 10;
    collisionType = entityNS::CIRCLE;
	active = true;
	shootTime = 0;
}

void Gun::setShootTime(float s)
{
	shootTime = s;
}


void Gun::update(float frameTime, bool& shoot)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y;     // move ship along Y

	shootTime += frameTime;
	
	if(shootTime > GUN_SHOOT_DELAY)
	{
		shoot = true;
		shootTime = 0;
	}
	else
	{
		shoot = false;
	}
}
