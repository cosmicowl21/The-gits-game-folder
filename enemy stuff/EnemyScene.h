#ifndef __ENEMY_SCENE_H__
#define __ENEMY_SCENE_H__

#include "cocos2d.h"
#include "ui/UIWidget.h"
#include "ui/GUIExport.h"
using namespace cocos2d;

class EnemyScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init()override;
    
	 void addTarget();
	 void spriteMoveFinished();
	 void addEnemyGhoul(float dt);
	 void addEnemyRaider(float st);
	 void addEnemyRobot(float xt);
    // a selector callback
   // void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(EnemyScene);
	void update(float) override;
	
private:
	cocos2d::Sprite* sprite;
    cocos2d::PhysicsWorld *sceneWorld;
void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world;};

//CCTMXTiledMap *_tileMap;
//CCTMXLayer *_background;
};
#endif // __ENEMY_SCENE_H__
