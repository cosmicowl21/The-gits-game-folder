#include "GameScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

USING_NS_CC;

#define BACKGROUND_MUSIC_SFX "main-game-theme.mp3"//sound init for music
#define TOWER_SHOOTING_SFX "grenade.mp3" //sound init for music
#define DEATH_SOUND_SFX "whip.mp3"//sound for the enemy death 

enum class PhysicsCategory {
	None = 0,
	Monster = (1 << 0),    // 1
	Projectile = (1 << 1), // 2
	//All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
};

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//red box around colisions

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}
	// 2
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto winSize = Director::getInstance()->getVisibleSize();
	// 3
	auto backgroundSprite = Sprite::create("backgroundCastle.png");
	backgroundSprite->setPosition(Point(winSize.width / 2 + origin.x, winSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);
	// 4
	_player = Sprite::create("cannon.png");//creating the player 
	_player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));//setting the players location 
	this->addChild(_player);//adding the player to the scene

	_player2 = Sprite::create("castle.png");//creating the player 2
	_player2->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.7));//setting the players location 
	 this->addChild(_player2);//adding the player to the scene


	srand((unsigned int)time(nullptr));
	this->schedule(schedule_selector(GameScene::addMonster), 1);//adding monsters randomly at 1 second intervial 

	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);//getting the mouse click form the player

	//breaking because of this ????????
	//auto eventListener2 = EventListenerTouchOneByOne::create();
	//eventListener2->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	//this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener2, _player2);//getting the mouse click form the player


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BACKGROUND_MUSIC_SFX, true);//playing the background music 

	return true;
}

void GameScene::addMonster(float dt)
{
	auto monster = Sprite::create("monster.png");//making the enemy 

	auto monsterSize = monster->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height),//
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	
	//setting up the physics 
	// 2
	physicsBody->setDynamic(true);
	// 3
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);
	



	monster->setPhysicsBody(physicsBody);
	// 1
	auto monsterContentSize = monster->getContentSize();
	auto selfContentSize = this->getContentSize();
	int minY = monsterContentSize.height / 2;
	int maxY = selfContentSize.height - monsterContentSize.height / 2;
	int rangeY = maxY - minY;
	int randomY = (rand() % rangeY) + minY;

	monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width / 2, randomY));
	this->addChild(monster);//adding enemy to the layer 

	// 2
	int minDuration = 2.0;
	int maxDuration = 4.0;
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	// 3
	auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width / 2, randomY));
	auto actionRemove = RemoveSelf::create();
	monster->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}

bool GameScene::onTouchBegan(Touch * touch, Event *unused_event)
{
	// 2
	Vec2 touchLocation = touch->getLocation();
	Vec2 offset = touchLocation - _player->getPosition();

	

	// 3
	if (offset.x < 0 ) 
	{
		return true;
	}

	// 4
	auto projectile = Sprite::create("cannonball.png");//making the projectile 
	projectile->setPosition(_player->getPosition());
	this->addChild(projectile);//adding it to the layer 

	

	//setting the phycis of the projectile 
	auto projectileSize = projectile->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Monster);
	projectile->setPhysicsBody(physicsBody);

	

	// 5
	offset.normalize();
	auto shootAmount = offset * 1000;

	// 6
	auto realDest = shootAmount + projectile->getPosition();
	
	// 7
	auto actionMove = MoveTo::create(2.0f, realDest);
	auto actionRemove = RemoveSelf::create();
	projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));



	SimpleAudioEngine::getInstance()->playEffect(TOWER_SHOOTING_SFX);//tower shooting sound 
	return true;
}

bool GameScene::onContactBegan(PhysicsContact &contact)
{
	auto nodeEnemy = contact.getShapeA()->getBody()->getNode();//enemy 
	auto nodeProjectile = contact.getShapeB()->getBody()->getNode();//projectile 

	
	nodeEnemy->removeFromParent();//remove the enemy 
	SimpleAudioEngine::getInstance()->playEffect(DEATH_SOUND_SFX);//enemy dying sound
	nodeProjectile->removeFromParent();//remove the projectile 
	
	return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
