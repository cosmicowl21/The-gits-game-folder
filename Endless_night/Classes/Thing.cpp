#include "Thing.h"
#include "Definitions.h"

USING_NS_CC;

Thing::Thing()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Thing::SpawnObject(Layer*Layer)
{
	CCLOG("Spawn Object");
}