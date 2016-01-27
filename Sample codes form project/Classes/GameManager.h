//Author: James Walsh 
//Student Number: K00175707
#pragma once
#include "cocos2d.h"//opens
#include "Creep.h"//opens
#include "Waypoint.h"//opens
#include "HelloWorldScene.h"//opens
#include "Projectile.h"//opens
#include "Wave.h"//opens
#include "GameObject.h"//opens
#include "Tower.h"//opens

USING_NS_CC;

class GameManager
{
public:

	HelloWorld* _gameLayer;
	static GameManager * getGame();
	void targets();
	//set all these up once i have stuff ready for them 
	Vector<Waypoint*>waypoints;//fix this later once i have stuff in waypoint
	Vector<Wave*>waves;
	Vector<Tower*> towers;
	Vector<Projectile*> projectiles;
	GameObject* _gameObjectLayer;

private:

	GameManager()
	{

	};

	static GameManager * g_pInstance;
};



