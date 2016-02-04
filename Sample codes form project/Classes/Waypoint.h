//Author: James Walsh 
//Student Number: K00175707
#pragma once
#include "cocos2d.h"//opens

USING_NS_CC;

class Waypoint :public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Waypoint);
};