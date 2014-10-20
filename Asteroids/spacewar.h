// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "planet.h"
#include "ship.h"
#include "bullet.h"
#include "enemyBullet.h"
#include "asteroid.h"
#include "textDX.h"
#include "gun.h"
#include "power.h"
#include <sstream>


//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager backgroundTexture;	// nebula texture
	TextureManager shipTextures;
	TextureManager asteroidTextures;
	TextureManager gunTexture;
	TextureManager bulletTexture;
	TextureManager enemyBulletTexture;
	TextureManager powerTexture;

	Ship    ship;           		// spaceship
	Image	background;					// backdrop image
	Bullet  bullets[MAX_BULLETS];	// array of bullets
	EnemyBullet enemyBullets[MAX_ENEMY_BULLETS];
	Asteroid asteroids[MAX_ASTEROIDS];	// array of bullets
	Gun		guns[MAX_GUNS];
	Power	power;

	// text fonts
	TextDX *dxFontGameOver;
	TextDX *dxFontScore;

	int asteroidCounter;
	int asterGroupSize;
	float asteroidSpawnTime;

	// flags
	bool shoot;
	float shootTime;
	bool gameOver;
	int score;
	bool powerupActive;
	float powerupTime;
	float timeSincePowerupSpawn;

public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "

	
	void spawnBullet(VECTOR2 pos, VECTOR2 vel);
	void spawnEnemyBullet(VECTOR2 pos, VECTOR2 vel);
	void spawnAsteroid(VECTOR2 pos, VECTOR2 vel);
	void spawnPowerup(VECTOR2 pos, VECTOR2 vel);

	void releaseAll();
    void resetAll();
};

#endif
