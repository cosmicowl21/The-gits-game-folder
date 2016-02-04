//Author: James Walsh 
//Student Number: K00175707
#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameObject : public Layer
{
public:
	Sprite* backround;
	Sprite* selectSpriteRange;
	Sprite* selectSprite;
	Vector<Sprite*> movableSprites;
	static GameObject* _sharObject;
	virtual bool init();
	static GameObject* shareObject;
	CREATE_FUNC(GameObject);
	virtual void onEnter();
};