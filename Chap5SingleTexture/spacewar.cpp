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
	
	if (!shipTexture.initialize(graphics, SHIP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Ship texture initialization failed"));
	if (!ship.initialize(graphics, 0,0,0, &shipTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error init ship"));
	ship.setX(GAME_WIDTH/2 - (ship.getWidth()*SHIP_IMAGE_SCALE)/2);
	ship.setY(GAME_HEIGHT/2 - (ship.getHeight()*SHIP_IMAGE_SCALE)/2);
	ship.setScale(SHIP_IMAGE_SCALE);

	shipSpeed = 120;


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

	if(input->isKeyDown(VK_SPACE))
	{
		MessageBeep((UINT) -1);
	}

	D3DXVECTOR2 direction(0,0);
	if(input->isKeyDown(VK_UP))
		direction.y = -1;
	if(input->isKeyDown(VK_DOWN))
		direction.y = 1;
	if(input->isKeyDown(VK_RIGHT))
		direction.x = 1;
	if(input->isKeyDown(VK_LEFT))
		direction.x = -1;
	D3DXVec2Normalize(&direction,&direction);
	
	ship.setX(ship.getX() + direction.x*shipSpeed*frameTime);
	ship.setY(ship.getY() + direction.y*shipSpeed*frameTime);

	if(ship.getX() < 0)
		ship.setX(0);
	if(ship.getX()+ship.getWidth()*ship.getScale() > GAME_WIDTH)
		ship.setX(GAME_WIDTH-ship.getWidth()*ship.getScale());
	if(ship.getY() < 0)
		ship.setY(0);
	if(ship.getY()+ship.getHeight()*ship.getScale() > GAME_HEIGHT)
		ship.setY(GAME_HEIGHT-ship.getHeight()*ship.getScale());

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

	ship.draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	shipTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
   
	shipTexture.onResetDevice();

    Game::resetAll();
    return;
}
