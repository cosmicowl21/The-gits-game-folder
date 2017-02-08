
#pragma once

#include "cocos2d.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class Level : public Object
{
public:

	TMXTiledMap *map;

	void loadMap(const char* name);
	TMXTiledMap * getMap();

	Point tileCoordinateToPosition(Point point);
	Point positionToTileCoordinate(Point point);
	vector<Rect> getCollisionTilesY(Point point, int direction);
	vector<Rect> getCollisionTilesX(Point point, int direction);

	Level(void);
	virtual ~Level(void);
};
