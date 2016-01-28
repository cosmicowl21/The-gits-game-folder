#include "EnemyScene.h"
#include "ui/CocosGUI.h"
//**********************************************************************************************************************
// EnemyScene contains all the enemy states,Ai,Enemy .resources used in this scene are included in the resources folder.
// student Name :conor Holmes
//student No:K00177426
//**********************************************************************************************************************


USING_NS_CC;
enum class physicsCategory{
	None = 0,
	Ghoul = (1 << 0),//1
	Projectile =(1 << 1), //2
	
};

Scene* EnemyScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = EnemyScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EnemyScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//std::string file = "BackgroundG.tmx";
	//auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	//_tileMap = TMXTiledMap::createWithXML(str->getCString(), "");
	//_background = _tileMap->layerNamed("GameBackground");

//	addChild(_tileMap, -1);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

   /* // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(EnemyScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

   

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);*/
	//sprite = Sprite::create("Hero.png");
	//sprite->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY);
	//sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//
	//_tileMap = new CCTMXTiledMap();
	//_tileMap->initWithTMXFile("BackgroundG.tmx");
	//_background = _tileMap->layerNamed("GameBackground");

	//this->addChild(_tileMap);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	// three towers use hero.png picture
	auto sprite = Sprite::create("hero.png");
	auto spriteSize = sprite->getContentSize();
	//auto physicsHero = PhysicsBody::createBox(Size(spriteSize.width, spriteSize.height));
		//PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//physicsHero->setDynamic(false);

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width /5  + origin.x, visibleSize.height /2 + origin.y));
	//sprite->setPhysicsBody(physicsHero);
	
	this->addChild(sprite, 0);

	auto tower = Sprite::create("hero.png");
	auto towerSize = sprite->getContentSize();
	//auto physicsTower = PhysicsBody::createBox(Size(towerSize.width, towerSize.height));
	//PhysicsMaterial(0.1f, 1.0f, 0.0f));
	// physicsTower->setDynamic(false);
	// position the sprite on the center of the screen
	tower->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y));
//	tower->setPhysicsBody(physicsTower);

	this->addChild(tower, 0);


	auto towerB = Sprite::create("hero.png");
	auto towerBSize = sprite->getContentSize();
	//auto physicsTowerB = PhysicsBody::createBox(Size(towerBSize.width, towerBSize.height),
	///PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//physicsTowerB->setDynamic(false);
	// position the sprite on the center of the screen
	towerB->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 1.2 + origin.y));
	//towerB->setPhysicsBody(physicsTowerB);

	this->addChild(towerB, 0);
	/* health bar here
	auto loading = UILoadingBar::create("emptybar.png");
	loading->setDirection(UILoadingBar::Direction::RIGHT);

	// something happened, change the percentage of the loading bar
	loading->setPercent(25);

	// more things happened, change the percentage again.
	loading->setPercent(35);

	this->addChild(loading);

	*/
	//this->scheduleUpdate();
	//the enemies are scheduled into the game scene from right to left towards the towers the enemies are randomized in no order Ghoul,Raider,and robot
	//from the void addEnemyGhoul,addEnemyRaider and addEnemyRobot methods
	srand((unsigned int)time(nullptr));
	this->schedule(schedule_selector(EnemyScene::addEnemyGhoul), 10.5);
	
	srand((unsigned int)time(nullptr));
	this->schedule(schedule_selector(EnemyScene::addEnemyRaider), 25.5);
    
	srand((unsigned int)time(nullptr));
	this->schedule(schedule_selector(EnemyScene::addEnemyRobot), 21.5);
	
    return true;
}
//enemy type 1 ghoul slow speed, 40% health, keep far away from tower as meele combat is good
void EnemyScene::addEnemyGhoul(float dt)
{
	auto ghoul = CCSprite::create("zombie.png");
	auto ghoulSize = ghoul->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(ghoulSize.width, ghoulSize.height));
		//PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);

	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	 
	//physicsBody->applyForce(Vec2(0,-0.5));
	ghoul->setPhysicsBody(physicsBody);
	

	// postion and size of enemy ghoul
	auto monsterContentSize = ghoul->getContentSize();
	auto selfContentSize = this->getContentSize();
	int minY = monsterContentSize.height / 2;
	int maxY = selfContentSize.height - monsterContentSize.height / 2;
	int rangeY = maxY - minY;
	int randomY = (rand() % rangeY) + minY;

	ghoul->setPosition(Vec2(selfContentSize.width + monsterContentSize.width / 2, randomY));
	this->addChild(ghoul);
	// min and max duration the enemy stays on screen
	int minDuration = 20.0;
	int maxDuration = 30.0;
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	//enemy moves to tower coords and deleted from screen when collides with the towers
	auto actionMove = MoveTo::create(randomDuration, Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 2 + origin.y));
	auto actionRemove = RemoveSelf::create();

	// create a BounceIn Ease Action
	auto move_ease_in = EaseSineOut::create(actionMove->clone());

	// create a delay that is run in between sequence events
	auto delay = DelayTime::create(0.25f);

	// create the sequence of actions, in the order we want to run them
	auto seq1 = Sequence::create(move_ease_in, delay,
		delay->clone(), nullptr);

	// run the sequence and repeat forever.
	ghoul->runAction(RepeatForever::create(seq1));
	ghoul->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}
//enemy type 2 Raider fast speed, 70% health, inadquite weapons carries poor quality weapons,average meele combat.
void EnemyScene::addEnemyRaider(float st)
{
	auto Raider = CCSprite::create("yellowMan.png");
	auto RaiderSize = Raider->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(RaiderSize.width, RaiderSize.height));
		//PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// postion and size of enemy Raider
	auto monsterContentSize = Raider->getContentSize();
	auto selfContentSize = this->getContentSize();
	int minY = monsterContentSize.height / 2;
	int maxY = selfContentSize.height - monsterContentSize.height / 2;
	int rangeY = maxY - minY;
	int randomY = (rand() % rangeY) + minY;

	Raider->setPosition(Vec2(selfContentSize.width + monsterContentSize.width / 2, randomY));
	Raider->setPhysicsBody(physicsBody);
	this->addChild(Raider);
	// min and max duration the enemy stays on screen
	int minDuration = 6.0;
	int maxDuration = 12.0;
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	////enemy moves to tower coords and deleted from screen when collides with the towers
	auto actionMove = MoveTo::create(randomDuration, Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 1.2 + origin.y));
	auto actionRemove = RemoveSelf::create();
	
	// create a BounceIn Ease Action
	auto move_ease_in =EaseSineInOut::create(actionMove->clone());

	// create a delay that is run in between sequence events
	auto delay = DelayTime::create(0.25f);

	// create the sequence of actions, in the order we want to run them
	auto seq1 = Sequence::create(move_ease_in, delay,
		delay->clone(), nullptr);

	// run the sequence and repeat forever.
	Raider->runAction(RepeatForever::create(seq1));
	Raider->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}

//enemy type 3 Robotknight average speed, 90% health, weapons are made out of good quality,poor close combat
void EnemyScene::addEnemyRobot(float xt)
{
	auto Robot = CCSprite::create("robot.png");
	auto robotSize = Robot->getContentSize();
	auto physicsBody = PhysicsBody::createBox(Size(robotSize.width, robotSize.height));
		//PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// postion and size of enemy robot
	auto monsterContentSize = Robot->getContentSize();
	auto selfContentSize = this->getContentSize();
	int minY = monsterContentSize.height / 2;
	int maxY = selfContentSize.height - monsterContentSize.height / 2;
	int rangeY = maxY - minY;
	int randomY = (rand() % rangeY) + minY;

	Robot->setPosition(Vec2(selfContentSize.width + monsterContentSize.width / 2, randomY));
	Robot->setPhysicsBody(physicsBody);
	this->addChild(Robot);
	// min and max duration the enemy stays on screen
	int minDuration = 10.0;
	int maxDuration = 30.0;
	int rangeDuration = maxDuration - minDuration;
	int randomDuration = (rand() % rangeDuration) + minDuration;

	//enemy moves to tower coords and deleted from screen when collides with the towers
	auto actionMove = MoveTo::create(randomDuration, Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 4 + origin.y));
	auto actionRemove = RemoveSelf::create();
	
	// create a BounceIn Ease Action
	auto move_ease_in = EaseBezierAction::create(actionMove->clone());

	// create a delay that is run in between sequence events
	auto delay = DelayTime::create(0.25f);

	// create the sequence of actions, in the order we want to run them
	auto seq1 = Sequence::create(move_ease_in, delay,
		delay->clone(), nullptr);

	// run the sequence and repeat forever.
	Robot->runAction(RepeatForever::create(seq1));
	Robot->runAction(Sequence::create(actionMove, actionRemove, nullptr));
}




void EnemyScene::update(float delta)
{
	auto postion = sprite->getPosition();
	postion.x -= 250 * delta;
	if (postion.x < 0 - (sprite->getBoundingBox().size.width / 2))
		postion.x = this->getBoundingBox().getMaxX()+sprite->getBoundingBox().size.width/2;
	sprite->setPosition(postion);
	/*
  //Director::getInstance()->end();
void EnemyScene::addTarget()
	{
		CCSprite *target = CCSprite::create("Target.png",
			CCRectMake(0, 0, 27, 40));

		// Determine where to spawn the target along the Y axis
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		int minY = target->getContentSize().height / 2;
		int maxY = winSize.height
			- target->getContentSize().height / 2;
		int rangeY = maxY - minY;
		// srand( TimGetTicks() );
		int actualY = (rand() % rangeY) + minY;

		// Create the target slightly off-screen along the right edge,
		// and along a random position along the Y axis as calculated
		target->setPosition(
			ccp(winSize.width + (target->getContentSize().width / 2),
			actualY));
		this->addChild(target);

		// Determine speed of the target
		int minDuration = (int)2.0;
		int maxDuration = (int)4.0;
		int rangeDuration = maxDuration - minDuration;
		// srand( TimGetTicks() );
		int actualDuration = (rand() % rangeDuration)
			+ minDuration;

		// Create the actions
		CCFiniteTimeAction* actionMove =
			CCMoveTo::create((float)actualDuration,
			ccp(0 - target->getContentSize().width / 2, actualY));
		CCFiniteTimeAction* actionMoveDone =
			CCCallFuncN::create(this,
			callfuncN_selector(EnemyScene::spriteMoveFinished));
		target->runAction(CCSequence::create(actionMove,
			actionMoveDone, NULL));
	}



 void EnemyScene ::spriteMoveFinished((CCNode* sender)
	{
		CCSprite* sprite = (CCSprite*) sender;
		this->removeChild(sprite, true);
	}
	*/
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
  //  exit(0);
//#endif
}
