#include "enemyBullet.h"



EnemyBullet::EnemyBullet() : Entity()
{
	spriteData.width = enemyBulletNS::WIDTH;           // size of Ship1
    spriteData.height = enemyBulletNS::HEIGHT;
    spriteData.x = enemyBulletNS::X;                   // location on screen
    spriteData.y = enemyBulletNS::Y;
    spriteData.rect.bottom = enemyBulletNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = enemyBulletNS::WIDTH;
	spriteData.scale = enemyBulletNS::SCALE;

	velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    radius = enemyBulletNS::WIDTH/2.0;
    collisionType = entityNS::CIRCLE;
	active = false;
}


void EnemyBullet::update(float frameTime)
{
	Entity::update(frameTime);

	spriteData.x += frameTime * velocity.x;     // move ship along X 
    spriteData.y += frameTime * velocity.y;     // move ship along Y

	if (spriteData.x > GAME_WIDTH-enemyBulletNS::WIDTH*getScale())
    {
		setActive(false);
    }
    else if (spriteData.x < 0)
    {
        setActive(false);
	}
    if (spriteData.y > GAME_HEIGHT-enemyBulletNS::HEIGHT*getScale())
    {
        setActive(false);
	}
	else if (spriteData.y < 0)
	{
		setActive(false);
	}
}