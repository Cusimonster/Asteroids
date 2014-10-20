#include "power.h"


Power::Power() : Entity()
{
	spriteData.width = powerNS::WIDTH;           // size of Ship1
    spriteData.height = powerNS::HEIGHT;
    spriteData.x = powerNS::X;                   // location on screen
    spriteData.y = powerNS::Y;
    spriteData.rect.bottom = powerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = powerNS::WIDTH;
	spriteData.scale = powerNS::SCALE;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    radius = (powerNS::WIDTH + powerNS::HEIGHT)/4.0;
    collisionType = entityNS::CIRCLE;
	active = false;
}


void Power::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;
    spriteData.y += frameTime * velocity.y;

	setRadians(getRadians()+POWERUP_ROTATION_SPEED);

	if (spriteData.x > GAME_WIDTH+powerNS::WIDTH*getScale())
    {
		setActive(false);
    }
    else if (spriteData.x < 0)
    {
        setActive(false);
	}
    if (spriteData.y > GAME_HEIGHT+powerNS::HEIGHT*getScale())
    {
        setActive(false);
	}
	else if (spriteData.y < 0)
	{
		setActive(false);
	}
}