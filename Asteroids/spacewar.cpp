// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceship
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include <time.h>

extern time_t start;
extern double seconds_since_start;


VECTOR2 testCollisionVector;//NEC
//extern int asteroidCounter = 0;
//extern int asterGroupSize = 1;

//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{
	asteroidCounter = 0;
	asterGroupSize = 1;//NEC default should be 1...25 for testing
}

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

	//ship sprite sheet
	if (!shipTextures.initialize(graphics,SHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship textures"));

	//unarmed asteroid sprite sheet
	if (!asteroidTextures.initialize(graphics,ASTEROID_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship textures"));

	//---------------------------------------------

    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

    // planet
    if (!planet.initialize(this, planetNS::WIDTH, planetNS::HEIGHT, 2, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	//NEC: ship
	
	if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &shipTextures))
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

	//unarmed asteroids
	for(int i=0; i<MAX_ASTEROIDS; i++)
	{
		if (!asteroids[i].initialize(this, asteroidNS::WIDTH, asteroidNS::HEIGHT, 0, &asteroidTextures))//asteroidNS::TEXTURE_COLS
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullets"));
		asteroids[i].setCurrentFrame(0);
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

    planet.update(frameTime);
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i].getActive())
			bullets[i].update(frameTime);
	}
	
	
	seconds_since_start = difftime( time(0), start);
	//Begin Unarmed Asteroid spawning
	if(seconds_since_start == 10) asterGroupSize = 3;
	if(seconds_since_start == 20) asterGroupSize = 5;
	if(seconds_since_start == 30) asterGroupSize = 8;
	if(seconds_since_start == 40) asterGroupSize = 10;
	if(seconds_since_start == 60) asterGroupSize = 20;

	if(asteroidCounter < asterGroupSize && asteroidCounter < MAX_ASTEROIDS)
	{
		spawnAsteroid(VECTOR2(GAME_WIDTH, rand() % 600 + -100),VECTOR2(asteroidNS::SPEED + (rand() % 20), rand() % 100 + -50));
		asteroidCounter++;
	}

	for(int i = 0; i < asteroidCounter; i++)
	{
		if(!asteroids[i].getActive()) asteroidCounter--;
	}

	for(int i=0; i<MAX_ASTEROIDS; i++)
	{
			if(asteroids[i].getActive())
			asteroids[i].update(frameTime);
		
			if(i%2) asteroids[i].setRadians(asteroids[i].getRadians() + 0.001);//if an even index of the asteroids array, then rotate clockwise
			else asteroids[i].setRadians(asteroids[i].getRadians() - 0.001);//if an odd index of the asteroids array, then rotate counter clockwise
	}
	//End Unarmed Asteroid spawning
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
{
	for(int i = 0; i < MAX_ASTEROIDS; i++)
	{
		if(ship.collidesWith(asteroids[i], testCollisionVector))
		{
			ship.setX(0);//ship.setActive(false);
			asteroids[i].setActive(false);
		}
		for(int j =0; j< MAX_BULLETS; j++)
		{
			
			if(asteroids[i].collidesWith(bullets[j],testCollisionVector))
			{
				asteroids[i].setX(0);
				bullets[j].setX(0);
			}
		}
	}
	
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    nebula.draw();                          // add the orion nebula to the scene
    planet.draw();                          // add the planet to the scene
    ship.draw();                            // add the spaceship to the scene
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i].getActive())
			bullets[i].draw();
	}
	for(int i=0; i<MAX_ASTEROIDS; i++)
	{
		if(asteroids[i].getActive())
			asteroids[i].draw();
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

//
// activate new Asteroid
//
void Spacewar::spawnAsteroid(VECTOR2 pos, VECTOR2 vel)
{
	Asteroid* first = nullptr;
	for(int i=0; i<MAX_ASTEROIDS; i++)
	{
		if(!(asteroids[i].getActive()))
		{
			first = &asteroids[i];
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
	shipTextures.onLostDevice();
	asteroidTextures.onLostDevice();
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
	shipTextures.onResetDevice();
	asteroidTextures.onResetDevice();
    Game::resetAll();
    return;
}
