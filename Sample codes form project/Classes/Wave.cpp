//Author: James Walsh 
//Student Number: K00175707
#include "Wave.h"//opens

USING_NS_CC;

bool Wave::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

Wave* Wave::initWithCreep(Creep* creep, double SpawnRate, int TotalCreeps)
{
	this->creepType = creep;
	this->spawnRate = SpawnRate;
	this->totalCreeps = TotalCreeps;

	return this;
}