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
#include "asteroid.h"

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager nebulaTexture;   // nebula texture
    TextureManager gameTextures;    // game texture
	TextureManager shipTextures; 
	TextureManager asteroidTextures; 

    Ship    ship;           		// spaceship
    Planet  planet;                 // the planet
    Image   nebula;                 // backdrop image
	Bullet  bullets[MAX_BULLETS];   // array of bullets
	Asteroid asteroids[MAX_ASTEROIDS];   // array of bullets

	int asteroidCounter;
	int asterGroupSize;

	// flags
	bool shoot;
	float shootTime;
	bool gameOver;

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
	void spawnAsteroid(VECTOR2 pos, VECTOR2 vel);
	

	void releaseAll();
    void resetAll();
};

#endif
