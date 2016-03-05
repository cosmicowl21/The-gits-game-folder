#ifndef _END_GAME_SCENE_H__
#define _END_GAME_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameOverScene);

private:
	//void GoToLeaderBoard(cocos2d::Ref *sender);
	void GoToGameScene(cocos2d::Ref *sender);
	void GoToMainMenuScene(cocos2d::Ref *sender);
	void GoToLeaderBoard(cocos2d::Ref *sender);

};

#endif // _END_GAME_SCENE_H__