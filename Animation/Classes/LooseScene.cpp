#include "LooseScene.h"
#include "GameScene.h"
#include "LeaderBoard.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "Quit.h"

USING_NS_CC;

Scene* LooseScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LooseScene::create();


	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LooseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();//init size
	Vec2 origin = Director::getInstance()->getVisibleOrigin();// init the origin 

	auto label = Label::createWithTTF("BETTER LUCK NEXT TIME", "fonts/Marker Felt.ttf", 44);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(ccc3(255, 215, 0));
	this->addChild(label, 1);

	auto backgroundSprite = Sprite::create("GameOver.png");// main menu image 
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	auto titleSprite = Sprite::create();//image
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(titleSprite);

	//button mapping to other screens

	//when click play it goes to the game scene
	auto NewGame = MenuItemImage::create("newGame.png", "newGame.png", CC_CALLBACK_1(LooseScene::GoToGameScene, this));
	NewGame->setPosition(Point(visibleSize.width / 4 + origin.x, visibleSize.height / 5 + origin.y));

	//LeaderBoard
	auto Leaderboard = MenuItemImage::create("leaderboard.png", "leaderboard.png", CC_CALLBACK_1(LooseScene::GoToLeaderBoard, this));
	Leaderboard->setPosition(Point(visibleSize.width / 2.5 + origin.x, visibleSize.height / 5 + origin.y));

	//Exit button
	auto closeItem = MenuItemImage::create("quit.png", "quit.png", CC_CALLBACK_1(LooseScene::menuCloseCallback, this));
	closeItem->setPosition(Point(visibleSize.width / 1.66 + origin.x, visibleSize.height / 5 + origin.y));

	//Go to the main menu screen
	auto MainMenu = MenuItemImage::create("Mainmenu.png", "Mainmenu.png", CC_CALLBACK_1(LooseScene::GoToMainMenuScene, this));
	MainMenu->setPosition(Point(visibleSize.width / 1.3 + origin.x, visibleSize.height / 5 + origin.y));

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

void LooseScene::GoToGameScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void LooseScene::GoToMainMenuScene(Ref *sender)//go to game scene method implementation 
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void LooseScene::GoToLeaderBoard(Ref *sender)//go to game scene method implementation 
{
	auto scene = LeaderBoard::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void LooseScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

