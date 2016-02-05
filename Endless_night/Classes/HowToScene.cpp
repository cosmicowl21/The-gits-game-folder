#include "HowToScene.h"
#include "Definitions.h"
#include "MainMenuScene.h"
USING_NS_CC;

Scene* HowToScene::createScene()
{
	auto scene = Scene::create();
	
	auto layer = HowToScene::create();

	scene->addChild(layer);

	return scene;
}

bool HowToScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto backgroundSprite = Sprite::create("background.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	auto back = MenuItemImage::create("back_button.png", "back_button.png", CC_CALLBACK_1(HowToScene::GoToMainMenuScene, this));
	back->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto back_button = Menu::create(back, NULL);
	back_button->setPosition(Point::ZERO);
	this->addChild(back_button);

	return true;
}

void HowToScene::GoToMainMenuScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}