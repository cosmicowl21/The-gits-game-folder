#ifndef _WAYPOINTS_H_
#define _WAYPOINTS_

#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class Waypoints :public Node{
public:

		Waypoints();
		~Waypoints();
		static Waypoints* nodeWithTheGame(GameScene* game, Point locaiton);
		bool initWiththeGame(GameScene* game, Point location);

		void Draw();
		CC_SYNTHESIZE(Point, _myPostion, MyPostion);
		CC_SYNTHESIZE(Waypoints*, _nextWaypoint, NextWaypoint);
private:
	GameScene* theGame;
};

#endif// Waypoints