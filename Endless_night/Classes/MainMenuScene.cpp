#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "TheOptionsScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

#define MENU_SFX "menu.mp3"//sound for the splash screen


USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenuScene::create();
	

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto backgroundSprite = Sprite::create("Endless_Night.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MENU_SFX);//menu sound 

	auto titleSprite = Sprite::create();//image
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height - titleSprite->getContentSize().height));
	this->addChild(titleSprite);

	//when click play it goes to the game scene
	auto NewGame = MenuItemImage::create("newGame.png","newGame.png",CC_CALLBACK_1(MainMenuScene::GoToGameScene,this));
	NewGame->setPosition(Point(visibleSize.width / 5 + origin.x, visibleSize.height / 3 + origin.y));

	//options
	auto options = MenuItemImage::create("options.png", "options.png", CC_CALLBACK_1(MainMenuScene::GoToTheOptionsScene, this));
	options->setPosition(Point(visibleSize.width / 2.5 + origin.x, visibleSize.height / 3 + origin.y));

	//credits
	//auto creditsItem = MenuItemImage::create("credits.png", "credits.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	//playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));

	//exit
	//auto exitItem = MenuItemImage::create("exit.png", "exit.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
	//playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 3 + origin.y));

	auto menu = Menu::create(NewGame, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto optionsMenu = Menu::create(options, NULL);
	optionsMenu->setPosition(Point::ZERO);
	this->addChild(optionsMenu);
    return true;
}

void MainMenuScene::GoToGameScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void MainMenuScene::GoToTheOptionsScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = TheOptionsScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}





