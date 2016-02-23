

#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "TheOptionsScene.h"
#include "SimpleAudioEngine.h"
//#include "Quit.h"
#include "HowToScene.h"

using namespace CocosDenshion;

#define MENU_SFX "menu.mp3"//sound for the splash screen


USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenuScene::create();
	

    // add layer as a child to scene banna
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (!Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();//init size
    Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 


	auto backgroundSprite = Sprite::create("Endless_Night.png");// main menu image 
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MENU_SFX);//menu sound 

	auto titleSprite = Sprite::create();//image
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(titleSprite);

	//button mapping to other screens

	//when click play it goes to the game scene
	auto NewGame = MenuItemImage::create("newGame.png","newGameClicked.png",CC_CALLBACK_1(MainMenuScene::GoToGameScene,this));
	NewGame->setPosition(Point(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y));

	//options
	auto options = MenuItemImage::create("options.png", "optionsClicked.png", CC_CALLBACK_1(MainMenuScene::GoToTheOptionsScene, this));
	options->setPosition(Point(visibleSize.width / 2.5 + origin.x, visibleSize.height / 5 + origin.y));

	auto closeItem = MenuItemImage::create("exit.png", "exitClicked.png", CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
	closeItem->setPosition(Point(visibleSize.width / 1.66 + origin.x, visibleSize.height / 5 + origin.y));

	
	auto NewGameButton = Menu::create(NewGame, NULL);
	NewGameButton->setPosition(Point::ZERO);
	this->addChild(NewGameButton);
	
	auto optionsMenu = Menu::create(options, NULL);
	optionsMenu->setPosition(Point::ZERO);
	this->addChild(optionsMenu);

	auto exit = Menu::create(closeItem, NULL);
	exit->setPosition(Point::ZERO);
	this->addChild(exit);
	
    return true; //apple
}

void MainMenuScene::GoToGameScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::GoToTheOptionsScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = TheOptionsScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

// end of game scene woo