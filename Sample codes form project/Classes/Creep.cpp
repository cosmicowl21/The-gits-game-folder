//Author: James Walsh 
//Student Number: K00175707
#include "Creep.h"
#include "Waypoint.h"
#include "GameManager.h"

USING_NS_CC;

bool Creep::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

Creep* Creep::initWithCreep(Creep* copyFrom)
{
	return NULL;
}

Creep* FastRedCreep::creep()
{
	auto creep = Creep::create();
	creep->sprite = Sprite::create("outlaw.png");
	creep->setScale(0.4);
	creep->addChild(creep->sprite, 0);
	creep->currentHP = 10;
	creep->moveDuration = 3;
	creep->CurrentWaypoint = 0;
	return creep;
}

Creep* StrongGreenCreep::creep()
{
	auto creep = Creep::create();
	creep->sprite = Sprite::create("mightyoutcast.png");
	creep->setScale(0.4);
	creep->addChild(creep->sprite, 0);
	creep->currentHP = 30;
	creep->moveDuration = 8;
	creep->CurrentWaypoint = 0;
	return creep;
}