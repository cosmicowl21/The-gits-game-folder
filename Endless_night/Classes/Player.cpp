
#include "Player.h"
#include "Global.h"

Player * Player::create()
{

	Player* pSprite = new Player();

	if (pSprite->initWithSpriteFrameName("idle"))
	{

		pSprite->setAnchorPoint(Point::ZERO);
		pSprite->player_size = Size(pSprite->getBoundingBox().size.width, pSprite->getBoundingBox().size.height);
	//	pSprite->player_size = Size(100.0f, 30.0f);
		return pSprite;
	}

	return NULL;
}

Rect Player::getCollisionBox() 
{

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + velocity_x,
		bbox.getMinY() + 1.0f,
		bbox.size.width,
		bbox.size.height);

	return rect;
}

Rect Player::getUpperCollisionBox() 
{

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + bbox.size.width * 0.33f,
		bbox.getMidY(),
		bbox.size.width * 0.4f,
		bbox.size.height * 1.5f);

	return rect;
}

void Player::updateState(float delta)
{

	if (velocity_x < 0) 
	{
		if (walk == NULL || walk->isDone() || direction != facing_left) 
		{
			direction = facing_left;
			walk->startWithTarget(this);
		}
	}

	if (velocity_y < 0) 
	{

	}

	if (velocity_x > 0) 
	{
		if (walk == NULL || walk->isDone() || direction != facing_right)
		{
			direction = facing_right;
			walk->startWithTarget(this);
		}
	}

	if (velocity_y > 0)
	{

	}

	if (velocity_x != 0) 
	{
		walk->step(delta);
	}

	if (direction == facing_right)
	{
		setFlippedX(true);
	}
	else
	{
		setFlippedX(false);
	}

	if (velocity_x == 0 && velocity_y == 0) 
	{
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("idle"));
		if (direction == facing_right)
		{
			setFlippedX(true);
		}
		else
		{
			setFlippedX(false);
		}
	}
	else if (velocity_y > 0 || velocity_y < 0)
	{
		setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump"));
		if (direction == facing_right)
		{
			setFlippedX(true);
		}
		else 
		{
			setFlippedX(false);
		}
	}

	/*setPositionX( getPositionX() + this->velocity_x);
	setPositionY( getPositionY() + this->velocity_y);*/
	if (velocity_x != 0) 
	{
		setPositionX(getPositionX() + velocity_x);
	}
	setPositionY(getPositionY() + velocity_y);
}

void Player::setupAnimation(const char* name) 
{

	if (walk != NULL)
		walk->release();
	

	walk = Animate::create(AnimationCache::getInstance()->getAnimation(name));
	walk->startWithTarget(this);
	walk->setDuration(0.80f);
	walk->retain();
}

Player::Player(void)
{
	velocity_x = 0;
	velocity_y = 0;
	direction = 0;

	facing_left = 1;
	facing_right = 2;
	facing_down = 3;
	facing_up = 4;
	facing_down_left = 5;
	facing_down_right = 6;
	facing_up_left = 7;
	facing_up_right = 8;

	grounded = true;
	jumping = false;

	walk = NULL;
	//setScale(0.6f);

	setupAnimation("walk");

}

Player::~Player(void)
{
}
