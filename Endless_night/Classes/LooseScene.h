#ifndef __LOOSE_SCENE_H__
#define __LOOSE	_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class LooseScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(LooseScene);

private:
	void GoToMainMenuScene(Ref *sender);
	void GoToGameScene(Ref *sender);
	void GoToLeaderBoard(Ref * sender);
	void menuCloseCallback(cocos2d::Ref* pSender);

};

#endif // __LOOSE_SCENE_H__
