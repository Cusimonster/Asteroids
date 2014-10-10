// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceship
// Chapter 6 spacewar.cpp v1.0
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

    // nebula texture
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

    // ship
    if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	//ship.setX(GAME_WIDTH/4);
	//ship.setY(GAME_HEIGHT/2);
	ship.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)


	// bullets
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if (!bullets[i].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &gameTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullets"));
		bullets[i].setCurrentFrame(bulletNS::BULLET_START_FRAME);
	}


	// flags
	shoot = false;
	shootTime = 0;


    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	ship.update(frameTime, shoot);
	shootTime += frameTime;
	if(shoot && shootTime >= SHOOT_DELAY)
	{
		spawnBullet(VECTOR2(ship.getX(),ship.getY()),VECTOR2(bulletNS::SPEED,0));
		audio->playCue(HIT);
		shootTime = 0;
	}

	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i].getActive())
			bullets[i].update(frameTime);
	}
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
	
	nebula.draw();                          // add the orion nebula to the scene
	ship.draw();                            // add the spaceship to the scene
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i].getActive())
			bullets[i].draw();
	}

    graphics->spriteEnd();                  // end drawing sprites
}

//
// activate new bullet
//
void Spacewar::spawnBullet(VECTOR2 pos, VECTOR2 vel)
{
	Bullet* first = nullptr;
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(!(bullets[i].getActive()))
		{
			first = &bullets[i];
			break;
		}
	}
	if(first != nullptr)
	{
		first->setActive(true);
		first->setVelocity(vel);
		first->setX(pos.x);
		first->setY(pos.y);
	}
}


//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    nebulaTexture.onLostDevice();
    gameTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    gameTextures.onResetDevice();
    nebulaTexture.onResetDevice();
    Game::resetAll();
    return;
}
