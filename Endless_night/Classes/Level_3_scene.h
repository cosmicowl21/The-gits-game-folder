#ifndef __LEVEL_3_SCENE_H__ // used so that hte header will only be used once per compile
#define __LEVEL_3_SCENE_H__

#include "cocos2d.h"// brining in cocos funcality 
#include "Box2D/Box2D.h"
using namespace cocos2d; // namespace for cococs so you dont have to use cocos2d:: every time 

class Level_3_Scene : public cocos2d::Layer
{

private:
	Sprite* _player;
	Sprite* _player2;
	cocos2d::Label * scoreLabel;

public:
	static cocos2d::Scene* createScene();// creating the scene from here 
	virtual bool init();// creating the bool init calss 
	void addMonster(float dt);// creating the monster class
	bool onTouchBegan(Touch * touch, Event *unused_event);
	bool onContactBegan(PhysicsContact &contact);
	void menuCloseCallback(cocos2d::Ref* pSender);
	bool scored;
	void SetIsScored();
	bool GetIsScored();
	int getScore();
	void GoToMainMenuScene(Ref *sender);
	void GoToLeaderBoard(Ref * sender);
	void GoToGameOverScene();

	CREATE_FUNC(Level_3_Scene);

};

#endif // __LEVEL_2SCENE_H__