#ifndef __LEADERBOARD_H__
#define __LEADERBOARD_H__

#include "cocos2d.h"
#include "Definitions.h"

class LeaderBoard : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(LeaderBoard);

private:
	void GoToMainMenuScene(cocos2d::Ref *sender);
};
#endif // __LEADERBOARD_H_
