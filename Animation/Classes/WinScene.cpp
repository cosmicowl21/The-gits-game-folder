#include "WinScene.h"
#include "GameScene.h"
#include "LeaderBoard.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "Quit.h"

USING_NS_CC;

Scene* WinScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = WinScene::create();
	

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool WinScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();//init size
    Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 

	auto label = Label::createWithTTF("CONGRADULATIONS", "fonts/Marker Felt.ttf", 44);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(ccc3(255, 215, 0));
	this->addChild(label, 1);

	auto backgroundSprite = Sprite::create("win.png");// main menu image 
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite); 

	auto titleSprite = Sprite::create();//image
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(titleSprite);

	//button mapping to other screens

	//when click play it goes to the game scene
	//when click play it goes to the game scene
	auto NewGame = MenuItemImage::create("newGame1.png", "newGame1.png", CC_CALLBACK_1(WinScene::GoToGameScene, this));
	NewGame->setPosition(Point(visibleSize.width / 4 + origin.x, visibleSize.height / 5 + origin.y));

	//LeaderBoard
	auto Leaderboard = MenuItemImage::create("leaderboard1.png", "leaderboard1.png", CC_CALLBACK_1(WinScene::GoToLeaderBoard, this));
	Leaderboard->setPosition(Point(visibleSize.width / 2.5 + origin.x, visibleSize.height / 5 + origin.y));

	//Exit button
	auto closeItem = MenuItemImage::create("quit1.png", "quit1.png", CC_CALLBACK_1(WinScene::menuCloseCallback, this));
	closeItem->setPosition(Point(visibleSize.width / 1.777 + origin.x, visibleSize.height / 5 + origin.y));

	//Go to the main menu screen
	auto MainMenu = MenuItemImage::create("Mainmenu.png", "Mainmenu.png", CC_CALLBACK_1(WinScene::GoToMainMenuScene, this));
	MainMenu->setPosition(Point(visibleSize.width / 1.333 + origin.x, visibleSize.height / 5 + origin.y));
	
	auto NewGameButton = Menu::create(NewGame, NULL);
	NewGameButton->setPosition(Point::ZERO);
	this->addChild(NewGameButton);

	auto Menu = Menu::create(MainMenu, NULL);
	Menu->setPosition(Point::ZERO);
	this->addChild(Menu);
	
	auto LeaderBoard = Menu::create(Leaderboard, NULL);
	LeaderBoard->setPosition(Point::ZERO);
	this->addChild(LeaderBoard);

	auto exit = Menu::create(closeItem, NULL);
	exit->setPosition(Point::ZERO);
	this->addChild(exit);
	
    return true;
}

void WinScene::GoToGameScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void WinScene::GoToMainMenuScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void WinScene::GoToLeaderBoard(Ref *sender)//go to game scene method implementation 
{
	auto scene = LeaderBoard::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void WinScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

