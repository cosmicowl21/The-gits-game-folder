//Author: James Walsh 
//Student Number: K00175707
#pragma once 
#include "cocos2d.h" // opens
#include "Creep.h" //opens
#include "Projectile.h"//opens

class Tower :public Sprite
{
public:
	int health;
	int cost;
	int range;
	Sprite* sprite;
	Creep* target;
	Sprite* selectSpriteRange;
	Creep* getClosesTarget();
	Creep* getClosestTarget();
	CREATE_FUNC(Tower);

};

class PowerFullTower : public Tower
{
public:
	static Tower*tower();
	bool virtual init();
	void towerLogic(float dt);
	void creepMoveFinnished();
	void finishFiring();
    //void creepMoveFinished();
	//PowerFullTower *creepMoveFinnished;
	Projectile* nextProjectile;
};