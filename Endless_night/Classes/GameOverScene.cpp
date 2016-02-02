#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "TheOptionsScene.h"
#include "SimpleAudioEngine.h"
#include "Quit.h"

using namespace CocosDenshion;

#define MENU_SFX "menu.mp3"//sound for the splash screen

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 

	auto backgroundSprite = Sprite::create("GameOver.png");// main menu image 
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MENU_SFX);//menu sound 
    

	auto closeItem = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));
	closeItem->setPosition(Point(visibleSize.width / 1.66 + origin.x, visibleSize.height / 5 + origin.y));

	auto exit = Menu::create(closeItem, NULL);
	exit->setPosition(Point::ZERO);
	this->addChild(exit);
    return true;
}
void GameOverScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}


