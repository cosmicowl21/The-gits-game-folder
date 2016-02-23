//
//conor holmes
//k00177426
//20 feb 16
//
#include "Waypoints.h"
USING_NS_CC;

Waypoints::Waypoints()
{
	_nextWaypoint = NULL;
}

Waypoints::~Waypoints()
{

}

Waypoints* Waypoints::nodeWithTheGame(GameScene* game, cocos2d::Point locaiton)
{
	Waypoints* pRet = new Waypoints();
	if (pRet && pRet->initWiththeGame(game, locaiton)){

	}
	else
	{
		CC_SAFE_RELEASE_NULL(pRet);
	}
	return pRet;
}
bool Waypoints::initWiththeGame(GameScene * game, cocos2d::Point location){


	bool bRet = false;
	do{
		theGame = game;
		_myPostion = location;
		this->setPosition(Point::ZERO);
		theGame->addChild(this);

		bRet = true;
	} while (0);
	return bRet;
}

void Waypoints::Draw()
{
	Node::draw();
}
#ifndef COCOS2D_DEBUG
DrawPrimitives::setDrawColor4F(0, 0f, 255.0f, 0, 255.0f);
DrawPrimitives::setcircle(_myPostion, 6, 360, 30, false);
DrawPrimitives::setcircle(_myPostion, 2, 360, 30, false);

if (_nextWaypoint){
	DrawPrimitives::drawLine(_myPostion, _nextWayPoints->_myPostion);
}
#endif //Debug