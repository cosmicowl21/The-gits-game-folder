//Author: James Walsh 
//Student Number: K00175707
#include "HelloWorldScene.h"//opens
#include"Tower.h"//opens
#include "GameManager.h"//opens
#include <Vector>//opens
#include <string>//opens
#include "Wave.h"//opens

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	auto GameObject = GameObject::shareObject;
	//m->_GameObjectLayer = GameObject;

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	std::string file = "";//image for game (map)
	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
	this->_tileMap = TMXTiledMap::createWithXML(str->getCString(), "");
	this->_background = _tileMap->layerNamed("Background");
	this->_background = _tileMap->layerNamed("Foreground");
	this->_background = _tileMap->layerNamed("Middleground");
	this->_background = _tileMap->layerNamed("Waypoints");
	addChild(_tileMap, -1);
	this->addWaypoint();
	this->addWaves();
	this->scheduleUpdate();
	this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0f);
	this->currentLevel = 0;

	return true;
}


void HelloWorld::FollowPath(Node *sender)
{
	Creep *creep = (Creep *)sender;

	Waypoint *waypoint = creep->getNextWaypoint();

	int moveDuration = creep->moveDuration;
	auto actionMove = MoveTo::create(moveDuration, waypoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(HelloWorld::FollowPath));
	creep->stopAllActions();
	creep->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

// Here we read the value from the class ‘creep’. And we make the enemy move. 

void HelloWorld::addWaves()
{
	GameManager *g = GameManager::getGame();

	Wave *wave = NULL;

	wave = Wave::create()->initWithCreep(FastRedCreep::creep(), 0.3, 75);
	g->waves.pushBack(wave);
	wave = NULL;

	wave = Wave::create()->initWithCreep(StrongGreenCreep::creep(), 1.0, 10);
	g->waves.pushBack(wave);
	wave = NULL;
}

// Here, we set the parameters for the class ‘Wave’ about the creep type, spawn rate and the number of the creep.

void HelloWorld::addWaypoint()
{
	GameManager *g = GameManager::getGame();
	auto *objects = this->_tileMap->objectGroupNamed("Objects");
	Waypoint *wp = NULL;

	std::string stringWithFormat = "Waypoint";
	int wayPointCounter = 0;
	ValueMap wayPoint;
	wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));

	while (wayPoint.begin() != wayPoint.end())
	{
		int x = wayPoint.at("x").asInt();
		int y = wayPoint.at("y").asInt();
		wp = Waypoint::create();
		wp->setPosition(ccp(x, y));
		g->waypoints.pushBack(wp);
		wayPointCounter++;
		wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	}
	wp = NULL;
}

void HelloWorld::addTarget()
{
	GameManager *g = GameManager::getGame();
	Wave *wave = this->getCurrentWave();

	if (wave->totalCreeps < 0)
	{
		return;
	}
	wave->totalCreeps--;

	Creep *target = NULL;
	int random = CCRANDOM_0_1() * 2;
	if (random == 0)
	{
		target = FastRedCreep::creep();
	}
	else
	{
		target = StrongGreenCreep::creep();
	}

	Waypoint *waypoint = target->getCurrentWaypoint();
	target->setPosition(waypoint->getPosition());
	waypoint = target->getNextWaypoint();
	this->addChild(target, 1);

	int moveDuration = target->moveDuration;
	auto actionMove = CCMoveTo::create(moveDuration, waypoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(HelloWorld::FollowPath));

	target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	target->tag = 1;
	g->targets.pushBack(target);

}

void HelloWorld::gameLogic(float dt)
{
	GameManager *g = GameManager::getGame();
	Wave *wave = this->getCurrentWave();
	static double lastTimeTargetAdded = 0;

	double now = 0;
	if (lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->spawnRate)
	{
		this->addTarget();
		lastTimeTargetAdded = now;
	}
}

void HelloWorld::update(float dt)
{
	GameManager *g = GameManager::getGame();
	Vector<Projectile*> projectilesToDelete;

	for each(Projectile *projectile in g->projectiles)
		// for (int i = 0; i < m->projectiles.size(); i++) // Use these code if your VC doesn’t support C++11.
	{
		// Projectile* projectile = (Projectile*)(m->projectiles.at(i)); // Use these code if your VC doesn’t support C++11.
		Rect projectileRect = Rect(projectile->getPositionX() - (projectile->getContentSize().width / 2),
			projectile->getPositionY() - (projectile->getContentSize().height / 2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

		Vector<Creep*> targetsToDelete;

		for each(Creep *target in g->targets)
		{
			Rect targetRect = Rect(target->getPositionX() - (target->sprite->getContentSize().width / 2),
				target->getPositionY() - (target->sprite->getContentSize().height / 2),
				target->sprite->getContentSize().width,
				target->sprite->getContentSize().height);

			if (projectileRect.intersectsRect(targetRect))
			{
				projectilesToDelete.pushBack(projectile);

				Creep *creep = target;
				creep->currentHP -= 1;

				if (creep->currentHP <= 0)
				{
					targetsToDelete.pushBack(creep);
				}
				break;
			}
		}

		
		for (int i = 0; i < targetsToDelete.size(); i++)
		{
			Creep* target = (Creep*)(targetsToDelete.at(i));

			g->targets.eraseObject(target);
			this->removeChild(target, true);
		}
	}

	for each(Projectile *projectile in projectilesToDelete)
		// for (int i =0; i < projectilesToDelete.size(); i++) // Use these code if your VC doesn’t support C++11.
	{
		// Projectile* projectile = (Projectile*)(projectilesToDelete.at(i)); // Use these code if your VC doesn’t support C++11.

		g->projectiles.eraseObject(projectile);
		this->removeChild(projectile, true);
	}
}


Wave *HelloWorld::getCurrentWave()
{
	GameManager *g = GameManager::getGame();
	Wave *wave = (Wave *)g->waves.at(this->currentLevel);

	return wave;
}

Wave *HelloWorld::getNextWave()
{
	GameManager *g = GameManager::getGame();

	this->currentLevel++;
	if (this->currentLevel > 1)
	{
		this->currentLevel = 0;
	}

	Wave *wave = (Wave *)g->waves.at(this->currentLevel);

	return wave;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif


bool HelloWorld::canBuildOnTilePosition(Point pos)
{
	Point towerLoc = this->tileCoordForPosition(pos);
	int tileGid = this->_background->getTileGIDAt(towerLoc);
	Value props = this->_tileMap->getPropertiesForGID(tileGid);
	ValueMap map = props.asValueMap();
	int type_int;
	if (map.size() == 0)
	{
		type_int = 0;
	}
	else
	{
		type_int = map.at("buildable").asInt();
	}

	if (1 == type_int)
	{
		return true;
	}
	return false;
}


void HelloWorld::addTower(Point pos)
{
	DataModel *m = DataModel::getModel();

	Tower *target = NULL;
	Point towerLoc = this->tileCoordForPosition(pos);
	int tileGid = this->_background->tileGIDAt(towerLoc);
	Value props = this->_tileMap->propertiesForGID(tileGid);
	ValueMap map = props.asValueMap();

	int type_int = map.at("buildable").asInt();
	if (1 == type_int)
	{
		target = PowerFullTower::tower();
		target->setPosition(ccp((towerLoc.x * 32) + 16, this->_tileMap->getContentSize().height - (towerLoc.y * 32) - 16));
		this->addChild(target, 1);
		target->setTag(1);
		m->towers.pushBack(target);
	}
	else
	{
		log("Tile Not Buildable");
	}
}


Point HelloWorld::boundLayerPos(Point newPos)
{
	Size winSize = CCDirector::getInstance()->getWinSize();
	Point retval = newPos;
	retval.x = MIN(retval.x, 0);
	retval.x = MAX(retval.x, _tileMap->getContentSize().width + winSize.width);
	retval.y = MIN(0, retval.y);
	retval.y = MAX(_tileMap->getContentSize().height + winSize.height, retval.y);
	return retval;
}