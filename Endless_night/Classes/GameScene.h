#ifndef __GAME_SCENE_H__ // used so that hte header will only be used once per compile
#define __GAME_SCENE_H__

#include "cocos2d.h"// brining in cocos funcality 

using namespace cocos2d; // namespace for cococs so you dont have to use cocos2d:: every time 

class GameScene : public cocos2d::Layer
{

private:
	//init players (towers)
	Sprite* _player;
	Sprite* _player2;

	//might be needed not sure yet 
	//void setPhysicsWorld(PhysicsWorld * world) { sceneWorld = world; };
	//PhysicsWorld * sceneWorld;
public:
	static cocos2d::Scene* createScene();// creating the scene from here 

	virtual bool init();// creating the bool init calss 

	void addMonster(float dt);// creating the monster class

	bool onTouchBegan(Touch * touch, Event *unused_event);

	void collisions();// unused for the moment

	// bool onContactBegin(PhysicsContact &contact);// failed collisions

	bool onContactBegan(PhysicsContact &contact);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	int enemiesKilled;

	void GoToMainMenuScene(Ref *sender);
	void GoToEndGameScene(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__