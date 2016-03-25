/*#ifndef __PAUSE_MENU_SCENE_H__
#define __PASUE_MENU_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class PasueMenuScene : public cocos2d::Layer
{
public:
static cocos2d::Scene* createScene();

virtual bool init();

// implement the "static create()" method manually
CREATE_FUNC(MainMenuScene);

private:
void GoToMainMenuScreen(Ref *sender);
void GoToGameScene(Ref *sender);
void menuCloseCallback(cocos2d::Ref* pSender);


};

#endif // __MAIN_MENU_SCENE_H__*/