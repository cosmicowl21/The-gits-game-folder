#include "Mini_Boss_Scene.h"//bringing in the game scene
#include "SimpleAudioEngine.h"//iporting the audio engine
#include "MainMenuScene.h"
#include "Definitions.h"
#include "LeaderBoard.h"
#include "Database.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "ui/CocosGUI.h"
#include <iostream>

unsigned int score4;

using namespace CocosDenshion; // namespace for audio engine 
using namespace cocos2d;

USING_NS_CC;

#define BOSS_MUSIC_SFX "Boss.mp3"//sound init for music
#define TOWER_SHOOTING_SFX "grenade.mp3" //sound init for music
#define DEATH_SOUND_SFX "whip.mp3"//sound for the enemy death 
#define COCOS2D_DEBUG 1

enum class PhysicsCategory
{
	None = 0,
	Boss = (1 << 0),// 1
	Monster = (1 << 0),
	Projectile = (1 << 1), // 2
						   //All = PhysicsCategory::Monster | PhysicsCategory::Projectile // 3
};

Scene* Mini_Boss_Scene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();//creating the scene with added physcis engine 
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));//setting the gravity to fall in whaterver way via x/y coordnate 
													 //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);//red box around colisions

													 // 'layer' is an autorelease object
	auto layer = Mini_Boss_Scene::create();//creating the game layer 

										   // add layer as a child to scene
	scene->addChild(layer);//adding the layer to the scene 

						   // return the scene
	return scene;//returning the scene so it can be made 
}

// on "init" you need to initialize your instance
bool Mini_Boss_Scene::init()//initing the game so the scene can be made 
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}//code like this for consisinsty 
/*
	GameScene game;
	score = game.getScore();
	CCLOG("Score: init: %d", score);
	*/
	 // 2
	auto origin = Director::getInstance()->getVisibleOrigin();//setting up the origin 
	auto winSize = Director::getInstance()->getVisibleSize();// as well as the window size or the visible size as well 
															 // 3
	auto backgroundSprite = Sprite::create("backgroundCastle.png");// creating the background and adding a sprite
																   // setting the postition of the sprite on screen  using the size of the window
	backgroundSprite->setPosition(Point(winSize.width / 2 + origin.x, winSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);//adding the bacground to the scene
									 // 4
	_player = Sprite::create("cannon.png");//creating the player, player is made in the header file 
	_player->setPosition(Vec2(winSize.width * 0.1, winSize.height * 0.5));//setting the players location 
	this->addChild(_player);//adding the player to the scene
	addMiniBoss();
	//this->schedule(schedule_selector(Mini_Boss_Scene::addMiniBoss));
	// this is not used now as the mini boss is the only enemy on screen
	//adding monsters randomly at ? per second intervial 
	srand((unsigned int)time(nullptr));
	this->schedule(schedule_selector(Mini_Boss_Scene::addMonster), 1);

	//this->schedule(schedule_selector(GameScene::GoToGameOverScene), 20.0f);

	//getting the mouse click form the player
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = CC_CALLBACK_2(Mini_Boss_Scene::onTouchBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, _player);

	// second tower will go here, have to get tbe collisions working for the aim

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Mini_Boss_Scene::onContactBegan, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//playing the background music 
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BOSS_MUSIC_SFX, true);

	// button to go back to the main menu 
	// button to go back to the main menu 
	auto menu = MenuItemImage::create("menu.png", "menuClicked.png", CC_CALLBACK_1(Mini_Boss_Scene::GoToMainMenuScene, this));
	menu->setPosition(Point(winSize.width * 0.1, winSize.height * 1));// change the size of the image in your recouce folder to maxamise efficinty 

	auto backToMenu = Menu::create(menu, NULL);
	backToMenu->setPosition(Point::ZERO);
	this->addChild(backToMenu);

	const float ScoreFontSize = 22;
	const float  ScorePostitionX = 24;
	const float ScorePostitionY = 12;
	score4 = 0;//

	__String *tempScore = __String::createWithFormat("Score:%i", score4);//

	scoreLabel = Label::create(tempScore->getCString(), "fonts/Marker felt.ttf", winSize.height* SCORE_FONT_SIZE);
	scoreLabel->setColor(Color3B::RED);
	scoreLabel->setAnchorPoint(ccp(0, 1));
	scoreLabel->setPosition(winSize.width / 2 + origin.x, winSize.height * SCORE_FONT_SIZE);

	this->addChild(scoreLabel, 1000);
	towerHp = 5;

	__String *tempLives = __String::createWithFormat("Lives:%d", towerHp);

	livesLabel = Label::create(tempLives->getCString(), "fonts/Marker felt.ttf", winSize.height* LIVES_FONT_SIZE);
	livesLabel->setColor(Color3B::RED);
	livesLabel->setAnchorPoint(ccp(0, 1));
	livesLabel->setPosition(winSize.width / 3 + origin.x, winSize.height * LIVES_FONT_SIZE);

	this->addChild(livesLabel, 10);
	return true;// returning that all is ok as is a bool(booean class)

}//end is init()

void Mini_Boss_Scene::addMonster(float dt)
{
	auto monster = Sprite::create("Shadow1.png");//making the enemy 

												 //giving the monster some attributes 
	auto monsterSize = monster->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width, monsterSize.height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	// 3
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Monster);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);

	monster->setPhysicsBody(physicsBody);
	Vector<SpriteFrame*> animFrames(4);

	for (int i = 1; i < 5; i++)
	{
		std::stringstream ss;
		ss << "Shadow" << i << ".png";
		String str = ss.str();
		auto frame = SpriteFrame::create(ss.str(), Rect(0, 0, 60, 105));
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	auto animate = Animate::create(animation);
	monster->runAction(RepeatForever::create(animate));
	// 1
	// giving the monster some movement and coordnates
	auto monsterContentSize = monster->getContentSize();
	auto selfContentSize = this->getContentSize();
	int minY = monsterContentSize.height / 2;
	int maxY = selfContentSize.height - monsterContentSize.height / 2;
	int rangeY = maxY - minY;
	int randomY = (rand() % rangeY) + minY;

	monster->setPosition(Vec2(selfContentSize.width + monsterContentSize.width / 2, randomY));
	this->addChild(monster);//adding enemy to the layer 

							// 2
	int minDuration = 9.0;
	int maxDuration = 30.0;
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	// 3
	//moving and taking off when collided 
	auto actionMove = MoveTo::create(randomDuration, Vec2(-monsterContentSize.width / 2, randomY));
	auto actionRemove = RemoveSelf::create();
	monster->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}//end of monster 
 // this is for adding the monsters to the scene , not used at the moment

void Mini_Boss_Scene::addMiniBoss()
{
	auto MiniBoss = Sprite::create("miniboss1.png");//making the enemy 

													//giving the monster some attributes 
	auto MiniBossSize = MiniBoss->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(MiniBossSize.width, MiniBossSize.height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	// 3
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Boss);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Projectile);

	MiniBoss->setPhysicsBody(physicsBody);
	Vector<SpriteFrame*> animFrames(3);

	for (int i = 1; i < 4; i++)
	{
		std::stringstream ss;
		ss << "miniboss" << i << ".png";
		String str = ss.str();
		auto frame = SpriteFrame::create(ss.str(), Rect(0, 0, 500, 400));
		animFrames.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	auto animate = Animate::create(animation);
	MiniBoss->runAction(RepeatForever::create(animate));
	// 1
	// giving the monster some movement and coordnates
	MiniBossSize = MiniBoss->getContentSize();
	auto selfContentSize = this->getContentSize();
	int minY = MiniBossSize.height / 2;
	int maxY = selfContentSize.height - MiniBossSize.height / 2;
	int rangeY = maxY - minY;
	int randomY = (rand() % rangeY) + minY;

	MiniBoss->setPosition(Vec2(selfContentSize.width + MiniBossSize.width / 2, randomY));
	EnemyList.pushBack(MiniBoss);
	this->addChild(MiniBoss);//adding enemy to the layer 

							 // 2
	int minDuration = 9.0;
	int maxDuration = 30.0;
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	// 3
	//moving and taking off when collided 
	auto actionMove = MoveTo::create(randomDuration, Vec2(-MiniBossSize.width / 2, randomY));
	auto actionRemove = RemoveSelf::create();
	auto delay = DelayTime::create(60.0f);
	// create a sequence
	auto delaySequence = Sequence::create(delay, delay->clone(), delay->clone(),
		delay->clone(), nullptr);

	MiniBoss->runAction(Sequence::create(delay, actionMove, actionRemove, nullptr));


}// end of mini boss

bool Mini_Boss_Scene::onTouchBegan(Touch * touch, Event *unused_event)
{
	// 2
	//setting up the vecs and what they are doing 
	Vec2 touchLocation = touch->getLocation();
	Vec2 offset = touchLocation - _player->getPosition();

	// 3
	if (offset.x < 0) //offset is the area at which the "bullet" will fire 
	{
		return true;
	}

	// 4
	auto projectile = Sprite::create("spear.png");//making the projectile 
	projectile->setPosition(_player->getPosition());
	this->addChild(projectile);//adding it to the layer 



							   //setting the phycis of the projectile 
	auto projectileSize = projectile->getContentSize();
	auto physicsBody = PhysicsBody::createCircle(projectileSize.width / 2);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
	physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
	physicsBody->setContactTestBitmask((int)PhysicsCategory::Boss);
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


	// sound plays once the player clicks the screen 
	SimpleAudioEngine::getInstance()->playEffect(TOWER_SHOOTING_SFX);//tower shooting sound 
	return true;
}

bool Mini_Boss_Scene::onContactBegan(PhysicsContact &contact)
{
	auto nodeEnemy = contact.getShapeA()->getBody()->getNode();//could be enemy or visa veras 
	auto nodeProjectile = contact.getShapeB()->getBody()->getNode();//could be projectile or visa versa 

	if (nodeEnemy)
		nodeEnemy->removeFromParent();//remove the enemy 
	SimpleAudioEngine::getInstance()->playEffect(DEATH_SOUND_SFX);//enemy dying sound
	nodeProjectile->removeFromParent();//remove the projectile 
	CCLOG("point added");
	score4++;


	__String * tempScore = __String::createWithFormat("Score:%i", score4);
	scoreLabel->setString(tempScore->getCString());
	//if score reaches 10 new level or end game scene with transmitions to gameOverscene or new scene 

	if (score4 == 7)//
	{
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
	}

	return true;
}

int Mini_Boss_Scene::getScore()
{
	CCLOG("Score: %d", score4);
	return score4;
}

void Mini_Boss_Scene::menuCloseCallback(Ref* pSender)// setting up the close button "quit"
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0); // origallny in the code 
#endif
}

void Mini_Boss_Scene::GoToMainMenuScene(Ref *sender)
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSATION_TIME, scene));
}

//void GameScene::GoToGameOverScene(float dt)
//{
//auto scene = GameOverScene::createScene();
//Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
//}
