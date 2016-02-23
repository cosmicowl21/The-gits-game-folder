#ifndef __GAME_SCENE_H__ // used so that hte header will only be used once per compile
#define __GAME_SCENE_H__

#include "cocos2d.h"// brining in cocos funcality 
#include "Box2D/Box2D.h"
using namespace cocos2d; // namespace for cococs so you dont have to use cocos2d:: every time 

class GameScene : public cocos2d::Layer
{

private:
	CCTMXTiledMap*_level1Map;
	CCTMXLayer *_background;
	Sprite* _player;
	Sprite* _player2;
	unsigned int score;
	cocos2d::Label * scoreLabel;
	cocos2d::Label * livesLabel;
	int enemyDamage;
	int towerDamage;
	float towerfireRate;
	int maxHp;
	int currentHp;
	float walkingSpeed;
	int towerHp;
	bool gameEnded;
	bool gameOver;
	int enemyScore;

public:
	static cocos2d::Scene* createScene();// creating the scene from here 
	virtual bool init();// creating the bool init calss 
	void addMonster(float dt);// creating the monster class
	bool onTouchBegan(Touch * touch, Event *unused_event);
	bool onContactBegan(PhysicsContact &contact);
	bool onContactBeganEndGame(PhysicsContact &contact);
	void menuCloseCallback(cocos2d::Ref* pSender);
	bool scored;
	bool livesLeft;
	//~GameScene();
	void SetLives();
	bool GetLives();

	void SetIsScored();
	bool GetIsScored();
	void getHpDamage();
	void doGameOver();
	void addWayPoints();
	void GoToMainMenuScene(Ref *sender);
	void GoToGameOverScene();
	CC_SYNTHESIZE_RETAIN(Array*, _waypoints, Waypoints);
	
	CREATE_FUNC(GameScene);
	
};

#endif // __GAME_SCENE_H__