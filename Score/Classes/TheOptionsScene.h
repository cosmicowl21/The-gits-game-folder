#ifndef __TheOptionsScene_H__
#define __TheOptionsScene_H__

#include "cocos2d.h"

using namespace cocos2d; 

class TheOptionsScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(TheOptionsScene);

private:
	void GoToMainMenuScene(Ref *sender);
	
};

#endif __TheOptionsScene_H__