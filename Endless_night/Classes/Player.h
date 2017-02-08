
#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class Player : public Sprite
{
public:

	float velocity_x;
	float velocity_y;

	int direction;
	int facing_left;
	int facing_right;
	int facing_up;
	int facing_down;
	int facing_down_left;
	int facing_down_right;
	int facing_up_left;
	int facing_up_right;
	bool grounded;
	bool jumping;

	Animate *walk;
	Size player_size;

	Rect getCollisionBox();
	Rect getUpperCollisionBox();

	static Player* create();

	void updateState(float delta);
	void setupAnimation(const char* name);

	Player(void);
	virtual ~Player(void);
};
