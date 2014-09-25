// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw planet with transparency
// Chapter 5 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

	if (!sonyTexture.initialize(graphics, SONY_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Sony texture initialization failed"));
	if (!sony.initialize(graphics, 0,0,0, &sonyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init sony"));
	sony.setX(GAME_WIDTH/2 - (sony.getWidth()*SONY_IMAGE_SCALE)/2);
	sony.setY(GAME_HEIGHT/2 - (sony.getHeight()*SONY_IMAGE_SCALE)/2);
	sony.setScale(SONY_IMAGE_SCALE);


	
	sonyVel.xVel = 60;
	sonyVel.yVel = 60;


    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	//Unomment to get the image to move

	D3DXVECTOR2	pos;
	//pos.x = sony.getX() + sonyVel.xVel * frameTime;
	//sony.setX(pos.x);
//WRAP

 

//REFLECT
 

 ////////////////
// INPUT MODS
 ////////////////

	D3DXVECTOR2 direction(0,0);

	if (input->isKeyDown(VK_RIGHT))
		direction.x = 1;
	if (input->isKeyDown(VK_LEFT))
		direction.x = -1;
	if (input->isKeyDown(VK_DOWN))
		direction.y = 1;
	if (input->isKeyDown(VK_UP))
		direction.y = -1;

	D3DXVec2Normalize(&direction, &direction);

	pos.x = sony.getX() + sonyVel.xVel * frameTime * direction.x;
	sony.setX(pos.x);

	pos.y = sony.getY() + sonyVel.yVel * frameTime * direction.y;
	sony.setY(pos.y);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

	sony.draw();

	

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	sonyTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
   
	sonyTexture.onResetDevice();

    Game::resetAll();
    return;
}
