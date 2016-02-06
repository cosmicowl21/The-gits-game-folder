#include "LeaderBoard.h"
#include "Definitions.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* LeaderBoard::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LeaderBoard::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LeaderBoard::init()
{
    //super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("LEADERBOARD", "fonts/Marker Felt.ttf", 44);
    label->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(ccc3(255, 215, 0));
	this->addChild(label, 1);

	auto MainMenu = MenuItemImage::create("Mainmenu.png", "Mainmenu.png", CC_CALLBACK_1(LeaderBoard::GoToMainMenuScene, this));
	MainMenu->setPosition(Vec2(visibleSize.width / 2, origin.y + visibleSize.height / 4.5));

	auto menu1 = Menu::create(MainMenu, NULL);
	menu1->setPosition(Vec2::ZERO);
	this->addChild(menu1, 1);

	auto label2 = Label::createWithTTF("The Top 10 Scores are:", "fonts/Marker Felt.ttf", 33);
	label2->setPosition(Vec2(visibleSize.width /2, origin.y + visibleSize.height/1.2));
	label2->setColor(ccc3(160, 32, 240));
	this->addChild(label2, 1);

	auto label3 = Label::createWithTTF("1. ", "fonts/Marker Felt.ttf", 33);
	label3->setPosition(Vec2(visibleSize.width / 3, origin.y + visibleSize.height / 1.3));
	label3->setColor(ccc3(0, 0, 0));
	this->addChild(label3, 1);

	auto label4 = Label::createWithTTF("2. ", "fonts/Marker Felt.ttf", 33);
	label4->setPosition(Vec2(visibleSize.width / 3, origin.y + visibleSize.height / 1.38));
	label4->setColor(ccc3(0, 0, 0));
	this->addChild(label4, 1);

	auto label5 = Label::createWithTTF("3. ", "fonts/Marker Felt.ttf", 33);
	label5->setPosition(Vec2(visibleSize.width / 3, origin.y + visibleSize.height / 1.44));
	label5->setColor(ccc3(0, 0, 0));
	this->addChild(label5, 1);

	auto ExitGame = MenuItemImage::create("Exit.png", "Exit.png",
										  CC_CALLBACK_1(LeaderBoard::menuCloseCallback, this));
	ExitGame->setPosition(Vec2(visibleSize.width / 2, origin.y + visibleSize.height / 6.4));
	
	auto menu = Menu::create(ExitGame, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

 //This adds a background to the screen
    auto sprite = Sprite::create("Background2.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void LeaderBoard::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void LeaderBoard::GoToMainMenuScene(Ref* sender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}