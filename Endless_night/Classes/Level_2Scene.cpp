// this is going to be the mini boss fight

//include files
#include "Level_2Scene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameOverScene.h"

//namespaces
using namespace CocosDenshion;
using namespace cocos2d;
USING_NS_CC;

//defines
#define BACKGROUND_MUSIC_SFX "main-game-theme.mp3"
#define TOWER_SHOOTING_SFX "grenade.mp3"
#define DEATH_SOUND "whip.mp3"
#define COCOS2D_DEBUG 1;


enum class PhysicsCategory
{
	None = 0,
	Monster = (1 << 0),
	Projectile = (1 << 1),
	//All = PhysicsCategory::Monster | PhysicsCategory::Projectile;
};



Scene* Level_2Scene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
	auto layer = Level_2Scene::create();
	

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance



bool Level_2Scene::init()

{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size winSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto backgroundSprite = Sprite::create("backgroundCastle.png");
	backgroundSprite->setPosition(Point(winSize.width / 2 + origin.x, winSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	
	_player = Sprite::create("cannon");
	_player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));
	this->addChild(_player);

	// adding monsters here 
	this->schedule(schedule_selector(Level_2Scene::AddMiniBoss));

	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = CC_CALLBACK_2(Level_2Scene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Level_2Scene::onContactBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC_SFX, this);

	auto menu = MenuItemImage::create("menu.png","menuClicked.png",CC_CALLBACK_1(Level_2Scene::GoToMainMenucene,this));
	menu->setPosition(Point::ZERO);

	auto backToMenu = Menu::create(menu, NULL);
	backToMenu->setPosition(Point::ZERO);
	this->addChild(backToMenu);

    return true;
}// end of init()

void Level_2Scene::AddMiniBoss(float dt)
{
	auto miniBoss = Sprite::create("miniboss1.png");
	auto miniBossSize = miniBoss->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(miniBossSize.width, miniBossSize.height),
		 PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);;
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
	miniBoss->setPhysicsBody(physicsBody);
	this->addChild(miniBoss);
	// int min duration to go in here next Time to sleep yay

}

