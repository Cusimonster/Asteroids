#include "bullet.h"



Bullet::Bullet() : Entity()
{
	spriteData.width = bulletNS::WIDTH;           // size of Ship1
    spriteData.height = bulletNS::HEIGHT;
    spriteData.x = bulletNS::X;                   // location on screen
    spriteData.y = bulletNS::Y;
    spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = bulletNS::WIDTH;
	spriteData.scale = bulletNS::SCALE;

	velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    radius = bulletNS::WIDTH/2.0;
    collisionType = entityNS::CIRCLE;
	active = false;
}


void Bullet::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y;     // move ship along Y

	if (spriteData.x > GAME_WIDTH-bulletNS::WIDTH*getScale())
    {
		setActive(false);
    }
    else if (spriteData.x < 0)
    {
        setActive(false);
	}
    if (spriteData.y > GAME_HEIGHT-bulletNS::HEIGHT*getScale())
    {
        setActive(false);
	}
	else if (spriteData.y < 0)
	{
		setActive(false);
	}
}