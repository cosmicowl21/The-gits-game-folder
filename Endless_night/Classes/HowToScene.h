#ifndef __HOWTOSCENE_H__
#define __HOWTOSCENE_H__

#include "cocos2d.h"

using namespace cocos2d; 

class HowToScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(HowToScene);

private:
	void GoToMainMenuScene(Ref *sender);
	
};

#endif __HOWTOSCENE_H__