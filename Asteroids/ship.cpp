// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 7 ship.cpp v1.0

#include "ship.h"

//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
    spriteData.width = shipNS::WIDTH;           // size of Ship1
    spriteData.height = shipNS::HEIGHT;
    spriteData.x = shipNS::X;                   // location on screen
    spriteData.y = shipNS::Y;
    spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = shipNS::WIDTH;
	spriteData.scale = shipNS::SCALE;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = shipNS::SHIP_ANIMATION_DELAY;
    startFrame = shipNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = shipNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = shipNS::WIDTH/2.0 - 10.0;//shipNS::WIDTH/2.0;
    collisionType = entityNS::CIRCLE;
	direction.x = 0;
	direction.y = 0;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ship::update(float frameTime, bool& shoot)
{
    Entity::update(frameTime);

	//movement control
	direction.x = 0;
	direction.y = 0;
	if(input->isKeyDown(SHIP_UP))
	{
		direction.y = 1;
	}
	if(input->isKeyDown(SHIP_DOWN))
	{
		direction.y = -1;
	}
	if(input->isKeyDown(SHIP_LEFT))
	{
		direction.x = -1;
	}
	if(input->isKeyDown(SHIP_RIGHT))
	{
		direction.x = 1;
	}
	D3DXVec2Normalize(&direction,&direction);
	
	spriteData.x += frameTime * velocity.x * direction.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y * direction.y;     // move ship along Y

	//setting shoot flag
	if(input->isKeyDown(SHIP_SHOOT))
	{
		shoot = true;
	}
	else
	{
		shoot = false;
	}

    //wall-bounding
    if (spriteData.x > GAME_WIDTH-shipNS::WIDTH*getScale())
    {
        spriteData.x = GAME_WIDTH-shipNS::WIDTH*getScale();   
    } 
    else if (spriteData.x < GAME_WIDTH/20)
    {
        spriteData.x = GAME_WIDTH/20;
    }
    if (spriteData.y > GAME_HEIGHT-shipNS::HEIGHT*getScale())
    {
        spriteData.y = GAME_HEIGHT-shipNS::HEIGHT*getScale();
	}
	else if (spriteData.y < 0)
	{
		spriteData.y = 0;
	}
}
