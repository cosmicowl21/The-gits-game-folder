//Author: James Walsh 
//Student Number: K00175707
#pragma once
#include "cocos2d.h"//opens
#include"Waypoint.h"//opens

USING_NS_CC;

class Creep : public Sprite
{
public:
	int currentHP;
	int moveDuration;
	int CurrentWaypoint;
	int tag;
	Sprite* sprite;
	virtual bool init();
	Creep* initWithCreep(Creep* copyFrom);
	Waypoint* getNextWaypoint();
	Waypoint* getCurrentWaypoint();
	CREATE_FUNC(Creep);

	Waypoint* Creep::getCurrentWaypoint()
	{
		GameManager*g = GameManager::getGame();
		Waypont*waypoint = (Waypoint *)m->waypoints.at(this->currentWaypoint);
		return Waypoint;
	}
	Waypoint* Creep::getNextWaypoint()
	{
		DataModel* m = DataModel::getModel();

		if (this->curWaypoint != 7)
		{
			this->curWaypoint++;
		}
		else
		{
			this->curWaypoint = 0;
		}

		CCLOG("%d", this->curWaypoint); // Debugging.

		WayPoint *waypoint = (WayPoint *)m->waypoints.at(curWaypoint);
		return waypoint;
	}
};

class FastRedCreep : public Creep
{
public:
	static Creep* creep();
};

class StrongGreenCreep : public Creep
{
public:
	static Creep* creep();
};
