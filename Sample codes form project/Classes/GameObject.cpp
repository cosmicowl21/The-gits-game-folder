//Author: James Walsh 
//Student Number: K00175707
#include "GameObject.h"//opens
#include "GameManager.h"//opens

GameObject* GameObject::_sharObject;

bool GameObject::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size WinSize = CCDirector::getInstance()->getWinSize();

	//draw the background for the game
	CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888);//not my code
	backround = Sprite::create("background.png");//picture for the background
	backround->setScaleX(2);
	backround->setAnchorPoint((0, 0));
	this->addChild(backround);
	Vector<String*> images;// bringing in the images 
	images.pushBack(StringMake("stonetower.png"));//tower1
	images.pushBack(StringMake("icetower.png"));//tower2
	images.pushBack(StringMake("acidtower.png"));//tower3
	images.pushBack(StringMake("superiortower.png"));//tower4

	for (int i = 0; i < images.size(); i++)
	{
		String* image = images.at(i);
		auto *sprite = Sprite::create(image->getCString());
		float offsetFraction = ((float)(i + 1)) / (images.size() + 1);
		sprite->setScale(0.6);
		sprite->setPosition(ccp(WinSize.width*offsetFraction, 35));
		this->addChild(sprite);
		movableSprites.pushBack(sprite);
	}

	return true;


}

GameObject* GameObject::shareObject()
{
	if (_sharObject == NULL)
	{
		_sharObject = GameObject::create();
	}

	return _sharObject
}

void GameObject::onEnter()
{
	Layer::onEnter();
	
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


