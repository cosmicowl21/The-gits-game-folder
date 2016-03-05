#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
//#include "LeaderBoard.h"
#include "Database.h"
#include "Mini_Boss_Scene.h"
#include "ui/CocosGUI.h"
#include <iostream>

int Pscore;
std::string name = "Please enter your Name:";
ui::EditBox* Box;

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
	//super init first
	if (!Layer::init())
	{
		return false;
	}

	Mini_Boss_Scene game;
	Pscore = game.getScore();
	CCLOG("Score: init: %i", Pscore);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/* Add a menu item with "X" image, which is clicked to quit the program
	you may modify it.

	add a "close" icon to exit the progress. it's an autorelease object
	*/

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(GameOverScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/*
	Add a label that says Game Over
	Create and initialize the Game Over label
	Position the Game Over label in the center of the screen
	Add the Game Over label as a child to this layer
	*/

	auto label = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 40);

	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	this->addChild(label, 1);

	auto MainMenu = MenuItemImage::create("Mainmenu.png", "Mainmenu.png", CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
	MainMenu->setPosition(Vec2(visibleSize.width / 2, origin.y + visibleSize.height / 1.5));

	auto menu1 = Menu::create(MainMenu, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

	auto TryAgain = MenuItemImage::create("TryAgain.png", "TryAgain.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
	TryAgain->setPosition(Vec2(visibleSize.width / 2, origin.y + visibleSize.height / 1.8));

	auto menu2 = Menu::create(TryAgain, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);

	/*// LeaderBoard
	auto Leaderboard = MenuItemImage::create("leaderboard1.png", "leaderboard1.png", CC_CALLBACK_1(GameOverScene::GoToLeaderBoard, this));
	Leaderboard->setPosition(Point(visibleSize.width / 2.5 + origin.x, visibleSize.height / 5 + origin.y));
	
	auto menu4 = Menu::create(Leaderboard, NULL);
	menu4->setPosition(Vec2::ZERO);
	this->addChild(menu4, 1);
	*/
/*	auto Submit = MenuItemImage::create("Submit.png", "Submit.png", CC_CALLBACK_1(GameOverScene::GoToLeaderBoard, this));
	Submit->setPosition(Vec2(origin.x + visibleSize.width / 2, 70));

	auto menu3 = Menu::create(Submit, NULL);
	menu3->setPosition(Vec2::ZERO);
	this->addChild(menu3, 1);
	*/
	//This adds a background to the screen
	auto sprite = Sprite::create("Background.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto EBox = ui::EditBox::create(Size(200, 40), ".png");
	EBox->setPlaceHolder("Enter Name:");
	EBox->setFontSize(20);
	EBox->setMaxLength(10);
	EBox->setPosition(Vec2(origin.x + visibleSize.width / 2, 150));
	this->addChild(EBox, 1);

	Box = EBox;

	CCLOG("Score: %d", Pscore);
	auto nameLabel = Label::createWithTTF("Your Score: " + std::to_string(Pscore), "fonts/Marker Felt.ttf", 24);
	nameLabel->setColor(Color3B::YELLOW);
	nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, 200));
	this->addChild(nameLabel, 1);

	return true;
}

void GameOverScene::GoToGameScene(Ref* psender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

void GameOverScene::GoToMainMenuScene(Ref* psender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}
/*
void GameOverScene::GoToLeaderBoard(Ref* psender)
{
	Database d;
	d.write(Box->getText(), Pscore);

	auto scene = LeaderBoard::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}
*/
void GameOverScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}