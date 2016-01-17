#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameScene : public cocos2d::Layer
{

private:
	Sprite* _player;
	Sprite* _player2;

	//void setPhysicsWorld(PhysicsWorld * world) { sceneWorld = world; };
	//PhysicsWorld * sceneWorld;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void addMonster(float dt);

	bool onTouchBegan(Touch * touch, Event *unused_event);

	void collisions();

	// bool onContactBegin(PhysicsContact &contact);

	bool onContactBegan(PhysicsContact &contact);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__