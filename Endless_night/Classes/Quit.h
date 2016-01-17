#ifndef __QUIT_H__
#define __QUIT_H__

#include "cocos2d.h"

using namespace cocos2d;

class Quit : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(Quit);

private:
	
	void GoToQuitScene(Ref *sender);
};

#endif // __QUIT_H__