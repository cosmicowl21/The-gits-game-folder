
#ifndef __LEVEL_2_SCENE_H__
#define __LEVEL_2_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class Level_2Scene : public cocos2d::Layer
{
private:
	Sprite*_player;
	Sprite*_player2;
	unsigned int score;
	cocos2d::Label * scoreLabel;

public:
	// creating everything we need for the cpp file
    static cocos2d::Scene* createScene();
    virtual bool init();
	void AddMiniBoss(float dt);
	bool onTouchBegan(Touch * touch, Event * unused_event);
	bool onContactBegan(PhysicsContact &contact);
	void menuCloseClallback(cocos2d::Ref * pSender);
	bool scored;
	void SetIsScored();
	bool GetIsSocred();
	void GoToMainMenucene();
	void GoToGameOverScene();
    
	CREATE_FUNC(Level_2Scene);

private:
	
	void GoToQuitScene(Ref *sender);
};

#endif // __QUIT_H__
