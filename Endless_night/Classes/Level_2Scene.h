
#ifndef __LEVEL_2_SCENE_H__
#define __LEVEL_2_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Level_2Scene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
	CREATE_FUNC(Level_2Scene);

private:
	
	void GoToQuitScene(Ref *sender);
};

#endif // __QUIT_H__
