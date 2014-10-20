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
	dxFontGameOver = new TextDX();
	dxFontScore = new TextDX();
}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
	releaseAll();           // call onLostDevice() for every graphics item
	SAFE_DELETE(dxFontGameOver);
	SAFE_DELETE(dxFontScore);
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	
	srand(time(0));

	// TEXTURE INIT --------------------------------------------
    // background texture
    if (!backgroundTexture.initialize(graphics,SPACE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));

	//ship sprite sheet
	if (!shipTextures.initialize(graphics,SHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	//bullet texture
	if (!bulletTexture.initialize(graphics,BULLET_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));

	//enemy bullet texture
	if (!enemyBulletTexture.initialize(graphics,ENEMY_BULLET_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy bullet texture"));

	//unarmed asteroid sprite sheet
	if (!asteroidTextures.initialize(graphics,ASTEROID_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing asteroid texture"));

	//gun asteroid sprite sheet
	if (!gunTexture.initialize(graphics,GUN_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing gunsteroid texture"));

	//powerup texture
	if (!powerTexture.initialize(graphics,POWER_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup texture"));

	//-----------------------------------------------------

   

	
	// IMAGE/ENTITY INIT -------------------------------------

	// space image
    if (!background.initialize(graphics,0,0,0,&backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// ship
	if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &shipTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	ship.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
	ship.setCurrentFrame(shipNS::SHIP1_START_FRAME);
	ship.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)

	// bullets
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if (!bullets[i].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &bulletTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullets"));
		bullets[i].setCurrentFrame(bulletNS::BULLET_START_FRAME);
	}

	// enemy bullets
	for(int i=0; i<MAX_ENEMY_BULLETS; i++)
	{
		if (!enemyBullets[i].initialize(this, enemyBulletNS::WIDTH, enemyBulletNS::HEIGHT, enemyBulletNS::TEXTURE_COLS, &enemyBulletTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy bullets"));
		enemyBullets[i].setCurrentFrame(enemyBulletNS::BULLET_START_FRAME);
	}

	//unarmed asteroids
	for(int i=0; i<MAX_ASTEROIDS; i++)
	{
		if (!asteroids[i].initialize(this, asteroidNS::WIDTH, asteroidNS::HEIGHT, asteroidNS::TEXTURE_COLS, &asteroidTextures))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullets"));
		asteroids[i].setCurrentFrame(0);
	}

	//gun asteroids
	for(int i=0; i<MAX_GUNS; i++)
	{
		if (!guns[i].initialize(this, gunNS::WIDTH, gunNS::HEIGHT, gunNS::TEXTURE_COLS, &gunTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullets"));
		guns[i].setCurrentFrame(0);
		guns[i].setX(rand()%(GAME_WIDTH/25));
		guns[i].setY(rand()%(GAME_HEIGHT/(2*MAX_GUNS))+(GAME_HEIGHT/(4*MAX_GUNS))+(i*GAME_HEIGHT/MAX_GUNS));
		guns[i].setVelocity(VECTOR2(0,0));
		guns[i].setShootTime((((float)rand())/(float)RAND_MAX)*GUN_SHOOT_DELAY - GUN_START_DELAY);
	}

	// powerup
	if (!power.initialize(this, powerNS::WIDTH, powerNS::HEIGHT, powerNS::TEXTURE_COLS, &powerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup"));
	
	//------------------------------------------------------------

	// DIRECTX FONT INIT ------------------------------------------

	if(dxFontGameOver->initialize(graphics, 64, false, true, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	if(dxFontScore->initialize(graphics, 32, false, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing DirectX font"));

	//--------------------------------------------------------------

	// flags & game values
	shoot = false;
	shootTime = 0;
	gameOver = false;
	score = 0;
	powerupActive = false;
	powerupTime = 0;
	timeSincePowerupSpawn = 0;

	asteroidCounter = 0;
	asterGroupSize = 1;//NEC default should be 1...25 for testing
	asteroidSpawnTime = 0;

    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	if(input->isKeyDown(ESC_KEY))
	{
		exitGame();
	}

	if(ship.getActive())
	{
		ship.update(frameTime, shoot);
		if(powerupActive)
		{
			shootTime += 3*frameTime;
			powerupTime += frameTime;
			if(powerupTime >= POWERUP_DURATION)
			{
				powerupActive = false;
			}
		}
		else
		{
			shootTime += frameTime;
		}
		
		if(shoot && shootTime >= SHIP_SHOOT_DELAY)
		{
			spawnBullet(VECTOR2(ship.getX()+(shipNS::SCALE*ship.getWidth()*3)/4,
								ship.getY()+(shipNS::SCALE*ship.getHeight()/2)),
								VECTOR2(bulletNS::SPEED,0));
			audio->playCue(PEW);
			shootTime = 0;
		}
	}

	if(timeSincePowerupSpawn >= POWERUP_FREQUENCY)
	{
		spawnPowerup(VECTOR2(GAME_WIDTH,(GAME_HEIGHT/4)+rand()%(GAME_HEIGHT/2)),VECTOR2(-1*powerNS::SPEED,0));
		timeSincePowerupSpawn = 0;
	}
	timeSincePowerupSpawn += frameTime;

	for(int i=0; i<MAX_GUNS; i++)
	{
		if(guns[i].getActive())
		{
			guns[i].update(frameTime, shoot);
			if(shoot)
			{
				spawnEnemyBullet(VECTOR2(guns[i].getX()+(gunNS::SCALE*guns[i].getWidth()*3)/4,
										 guns[i].getY()+(gunNS::SCALE*guns[i].getHeight()*3)/8),
										 VECTOR2(enemyBulletNS::SPEED,0));
				audio->playCue(PEW);
			}
		}
	}

	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(bullets[i].getActive())
			bullets[i].update(frameTime);
	}

	for(int i=0; i<MAX_ENEMY_BULLETS; i++)
	{
		if(enemyBullets[i].getActive())
			enemyBullets[i].update(frameTime);
	}

	if(power.getActive())
	{
		power.update(frameTime);
	}
	
	seconds_since_start = difftime( time(0), start);
	//Begin Unarmed Asteroid spawning
	if(seconds_since_start == 10) asterGroupSize = 3;
	if(seconds_since_start == 20) asterGroupSize = 5;
	if(seconds_since_start == 30) asterGroupSize = 8;
	if(seconds_since_start == 40) asterGroupSize = 10;
	if(seconds_since_start == 60) asterGroupSize = 20;

	asteroidSpawnTime += frameTime;
	if(asteroidCounter < asterGroupSize && asteroidCounter < MAX_ASTEROIDS && asteroidSpawnTime > ASTEROID_SPAWN_DELAY)
	{
		VECTOR2 newpos = VECTOR2(GAME_WIDTH, rand() % ((GAME_HEIGHT*7)/8+asteroidNS::HEIGHT)-GAME_HEIGHT/8-asteroidNS::HEIGHT);
		VECTOR2 newdir = VECTOR2(GAME_WIDTH/6, rand() % GAME_HEIGHT) - newpos;
		D3DXVec2Normalize(&newdir,&newdir);
		spawnAsteroid(newpos,newdir*asteroidNS::SPEED);
		asteroidCounter++;
		asteroidSpawnTime = 0;
	}

	for(int i = 0; i < asteroidCounter; i++)
	{
		if(!asteroids[i].getActive()) asteroidCounter--;
	}

	for(int i=0; i<MAX_ASTEROIDS; i++)
	{
		if(asteroids[i].getActive())
		asteroids[i].update(frameTime);
		
		if(i%2) asteroids[i].setRadians(asteroids[i].getRadians() + ASTEROID_ROTATION_SPEED);//if an even index of the asteroids array, then rotate clockwise
		else asteroids[i].setRadians(asteroids[i].getRadians() - ASTEROID_ROTATION_SPEED);//if an odd index of the asteroids array, then rotate counter clockwise
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
		if(asteroids[i].getActive())
		{
			if(ship.collidesWith(asteroids[i], testCollisionVector))
			{
				ship.setActive(false);
				gameOver = true;
				audio->playCue(POW);
			}
			for(int j=0; j < MAX_BULLETS; j++)
			{	
				if(asteroids[i].collidesWith(bullets[j],testCollisionVector))
				{
					asteroids[i].setActive(false);
					bullets[j].setActive(false);
					audio->playCue(POW);
					score += int(asteroids[i].getX())/ASTEROID_POINTS;
				}
			}
		}
	}
	for(int i=0; i < MAX_ENEMY_BULLETS; i++)
	{
		if(enemyBullets[i].collidesWith(ship,testCollisionVector))
		{
			enemyBullets[i].setActive(false);
			ship.setActive(false);
			gameOver = true;
			audio->playCue(POW);
		}
	}
	for(int i=0; i < MAX_GUNS; i++)
	{
		if(guns[i].collidesWith(ship,testCollisionVector))
		{
			ship.setActive(false);
			gameOver = true;
			audio->playCue(POW);
		}
	}
	if(power.collidesWith(ship,testCollisionVector))
	{
		power.setActive(false);
		powerupActive = true;
		powerupTime = 0;
	}
	
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	std::stringstream scoreStream;
	scoreStream << "Score: " << score;

	graphics->spriteBegin();                // begin drawing sprites
	background.draw();

	if(gameOver)
	{
		dxFontGameOver->setFontColor(graphicsNS::RED);
		dxFontGameOver->print(GAME_OVER_MESSAGE,GAME_WIDTH/3,GAME_HEIGHT/3);
	}

	dxFontScore->setFontColor(graphicsNS::WHITE);
	dxFontScore->print(scoreStream.str(),GAME_WIDTH/4,0);

	for(int i=0; i<MAX_ASTEROIDS; i++)
	{
		if(asteroids[i].getActive())
			asteroids[i].draw();
	}
	for(int i=0; i < MAX_BULLETS; i++)
	{
		if(bullets[i].getActive())
			bullets[i].draw();
	}
	for(int i=0; i < MAX_ENEMY_BULLETS; i++)
	{
		if(enemyBullets[i].getActive())
			enemyBullets[i].draw();
	}
	if(power.getActive())
	{
		power.draw();
	}
	for(int i=0; i<MAX_GUNS; i++)
	{
		if(guns[i].getActive())
			guns[i].draw();
	}
	if(ship.getActive())
	{
		ship.draw();
	}
	
    graphics->spriteEnd();                  // end drawing sprites
}

//----------------------------------------
// activate new bullet
//----------------------------------------
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

//----------------------------------------
// activate new enemy bullet
//----------------------------------------
void Spacewar::spawnEnemyBullet(VECTOR2 pos, VECTOR2 vel)
{
	EnemyBullet* first = nullptr;
	for(int i=0; i<MAX_ENEMY_BULLETS; i++)
	{
		if(!(enemyBullets[i].getActive()))
		{
			first = &enemyBullets[i];
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

//----------------------------------------
// activate new Asteroid
//----------------------------------------
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
		first->setDegrees(rand());
	}
}

void Spacewar::spawnPowerup(VECTOR2 pos, VECTOR2 vel)
{
	if(!power.getActive())
	{
		power.setActive(true);
		power.setVelocity(vel);
		power.setX(pos.x);
		power.setY(pos.y);
		power.setDegrees(rand());
	}
}


//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
	dxFontGameOver->onLostDevice();
	dxFontScore->onLostDevice();
    backgroundTexture.onLostDevice();
	shipTextures.onLostDevice();
	asteroidTextures.onLostDevice();
	gunTexture.onLostDevice();
	powerTexture.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
	dxFontGameOver->onResetDevice();
	dxFontScore->onResetDevice();
	backgroundTexture.onResetDevice();
	shipTextures.onResetDevice();
	asteroidTextures.onResetDevice();
	gunTexture.onResetDevice();
	powerTexture.onResetDevice();
    Game::resetAll();
    return;
}
