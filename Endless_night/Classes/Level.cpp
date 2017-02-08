
#include "Level.h"
#include "Global.h"

void Level::loadMap(const char* mapname) {

	map = TMXTiledMap::create(mapname);
	map->retain();
}

TMXTiledMap * Level::getMap() {
	return map;
}

Point Level::tileCoordinateToPosition(Point point) {

	float x = floor(point.x * map->getTileSize().width * SCALE_FACTOR);
	float y = floor(point.y * map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);

}

Point Level::positionToTileCoordinate(Point point) {

	float x = floor(point.x / (map->getTileSize().width * SCALE_FACTOR));
	float y = floor(point.y / (map->getTileSize().height * SCALE_FACTOR));

	return Point((int)x, (int)y);
}

vector<Rect> Level::getCollisionTilesY(Point point, int direction) {

	vector<Rect> list;

	TMXLayer *walls = map->getLayer("walls");

	int mapheight = (int)map->getMapSize().height - 1;

	for (int b = -1; b < 2; b++) {

		Sprite *tile = walls->getTileAt(Point((int)point.x + b, mapheight - ((int)point.y + direction)));

		if (tile != NULL) {

			Rect tileRect = Rect();

			Point tmp = walls->positionAt(Point((int)point.x + b, mapheight - ((int)point.y + direction)));
			tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR);

			list.push_back(tileRect);
		}

	}

	return list;

}

vector<Rect> Level::getCollisionTilesX(Point point, int direction) {

	vector<Rect> list;

	TMXLayer *walls = map->getLayer("walls");

	int mapheight = (int)map->getMapSize().height - 1;

	for (int b = -1; b < 2; b++) {

		Sprite *tile = walls->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y + b)));

		if (tile != NULL) {

			Rect tileRect = Rect();

			Point tmp = walls->positionAt(Point((int)point.x + direction, mapheight - ((int)point.y + b)));
			tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR, map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR);

			list.push_back(tileRect);
		}

	}

	return list;
}

Level::Level(void)
{
}

Level::~Level(void)
{
	map->release();
}
