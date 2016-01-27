#ifndef __THING__H
#define  __THING__H

#include "cocos2d.h"

class Thing
{
public:
	Thing();

	void SpawnObject(cocos2d::Layer * Layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};


#endif  __THING__H