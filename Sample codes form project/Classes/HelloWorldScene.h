//Author: James Walsh 
//Student Number: K00175707
#pragma once

#include "cocos2d.h"//opens
#include "Creep.h"//opens
#include "Waypoint.h"//opens
#include "Wave.h" //opens
#include "GameObject.h"//opens

USING_NS_CC;


class HelloWorld : public cocos2d::Layer
{
public:
	int currentLevel;
	void addWaypoint();
	void addWaves();
	void FollowPath(Node *sender);
	void gameLogic(float dt);
	void addTarget();
	void addTower(Point pos);
	Point tileCoordForPosition(Point position);
	bool canBuildOnTilePosition(Point pos);
	Point boundLayerPos(Point newPos);

	Point position;
	GameObject *GameObject;
	virtual void update(float dt);
	Wave* getCurrentWave();
	Wave* getNextWave();

	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

private:
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_background;
};


