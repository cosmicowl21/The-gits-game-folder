#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Thing.h"
using namespace cocos2d;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:

	void GoToMainMenuScene(Ref *sender);
	void setPhysicsWorld(PhysicsWorld *world) { sceneWorld = world; };

	void SpawnObject(float dt);
	PhysicsWorld *sceneWorld;

	Thing thing;
};



#endif // __Game_SCENE_H__
