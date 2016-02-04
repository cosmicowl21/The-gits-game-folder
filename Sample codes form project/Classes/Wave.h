//Author: James Walsh 
//Student Number: K00175707
#pragma once
#include "cocos2d.h"//opens
#include "Creep.h"//opens

USING_NS_CC;

class Wave : public Node
{
public:
	Point position;
	int totalCreeps;
	double spawnRate;
	Creep* creepType;
	virtual bool init();
	Wave* initWithCreep(Creep* creep, double SpawnRate, int TotalCreeps);
	CREATE_FUNC(Wave);
};