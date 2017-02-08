#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Global.h"

using namespace CocosDenshion;
#define Music "Music.mp3"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SimpleAudioEngine::getInstance()->playBackgroundMusic(Music);
	level = new Level();
	level->loadMap("level1.tmx");
	level->retain();

	auto director = Director::getInstance();
	level->getMap()->setScale(SCALE_FACTOR);

	this->addChild(level->getMap());

	player = Player::create();
	player->retain();

	Point point = Point(10, 2);

	player->setPosition(level->tileCoordinateToPosition(point));

	Point origin = Director::getInstance()->getVisibleOrigin();
	Size wsize = Director::getInstance()->getVisibleSize();  //default screen size (or design resolution size, if you are using design resolution)
	Point *center = new Point(wsize.width / 2 + origin.x, wsize.height / 2 + origin.y);

	cameraTarget = Sprite::create();
	cameraTarget->setPositionX(player->getPositionX()); // set to players x
	cameraTarget->setPositionY(wsize.height / 2 + origin.y); // center of height

	cameraTarget->retain();

	this->addChild(player);
	this->schedule(schedule_selector(GameScene::updateScene));

	this->addChild(cameraTarget);

	rectWithBorder = DrawNode::create();
	Vec2 vertices[] =
	{
		Vec2(0, player->player_size.height),
		Vec2(player->player_size.width, player->player_size.height),
		Vec2(player->player_size.width, 0),
		Vec2(0,0)
	};

	rectWithBorder->drawPolygon(vertices, 4, Color4F(0.0f, 0.3f, 0.3f, 1), 0, Color4F(0.0f, 0.2f, 0.0f, 1));

	addChild(rectWithBorder);

	camera = Follow::create(cameraTarget, Rect::ZERO);
	camera->retain();

	loadEnemies();

	this->runAction(camera);
	return true;
}

void GameScene::loadEnemies() 
{

	Sprite *enemy1 = Sprite::create("mom.png");
	enemy1->setPosition(level->tileCoordinateToPosition(Point(30, 0.5)));
	enemy1->setAnchorPoint(Point::ZERO);
	enemy1->setScale(ENEMY_SCALE_FACTOR);
	enemy1->setFlippedX(true);
	enemy1->retain();

	enemyList.push_back(enemy1);
	this->addChild(enemy1);

	Sprite *enemy2 = Sprite::create("mom.png");
	enemy2->setPosition(level->tileCoordinateToPosition(Point(40, 0.5)));
	enemy2->setAnchorPoint(Point::ZERO);
	enemy2->setScale(ENEMY_SCALE_FACTOR);
	enemy2->setFlippedX(true);
	enemy2->retain();

	enemyList.push_back(enemy2);
	this->addChild(enemy2);


	Sprite *enemy3 = Sprite::create("mom.png");
	enemy3->setPosition(level->tileCoordinateToPosition(Point(55, 0.5)));
	enemy3->setAnchorPoint(Point::ZERO);
	enemy3->setScale(ENEMY_SCALE_FACTOR);
	enemy3->setFlippedX(true);
	enemy3->retain();

	enemyList.push_back(enemy3);
	this->addChild(enemy3);

	Sprite *enemy4 = Sprite::create("mom.png");
	enemy4->setPosition(level->tileCoordinateToPosition(Point(200, 0.5)));
	enemy4->setAnchorPoint(Point::ZERO);
	enemy4->setScale(ENEMY_SCALE_FACTOR);
	enemy4->setFlippedX(true);
	enemy4->retain();

	enemyList.push_back(enemy4);
	this->addChild(enemy4);

	Sprite *enemy5 = Sprite::create("mom.png");
	enemy5->setPosition(level->tileCoordinateToPosition(Point(200, 0.5)));
	enemy5->setAnchorPoint(Point::ZERO);
	enemy5->setScale(ENEMY_SCALE_FACTOR);
	enemy5->setFlippedX(true);
	enemy5->retain();

	enemyList.push_back(enemy5);
	this->addChild(enemy5);

}


void GameScene::updateScene(float delta) 
{

	cameraTarget->setPositionX(player->getPositionX());

	this->updatePlayer(delta);

}

void GameScene::updatePlayer(float delta) 
{

	if (std::find(heldKeys.begin(), heldKeys.end(), SPACEBAR) != heldKeys.end())
	{

		if (player->grounded && player->velocity_y <= 0) 
		{

			player->velocity_y = PLAYER_JUMP_VELOCITY;
			player->jumping = true;
			player->grounded = false;
		}

	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end())
	{

		player->velocity_x = PLAYER_MAX_VELOCITY;

		player->facing_right = true;
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end())
	{

		player->velocity_x = -PLAYER_MAX_VELOCITY;
		player->facing_right = false;
	}

	player->velocity_y -= GRAVITY;

	Rect player_rect = player->getBoundingBox();

	Point tmp;
	vector<Rect> tiles;
	tiles.clear();

	// center of player's sprite
	tmp = level->positionToTileCoordinate(Point(player->getPositionX() + player->player_size.width * 0.5f, player->getPositionY() + player->player_size.height * 0.5f));

	if (player->velocity_x > 0)
	{
		tiles = level->getCollisionTilesX(tmp, 1);
	}
	else
	{
		tiles = level->getCollisionTilesX(tmp, -1);
	}

	player_rect.setRect(
		player->getBoundingBox().getMinX() + player->velocity_x,
		player->getBoundingBox().getMinY() + 1.0f, // dont let the rectangle touch the ground otherwise, will count as collision
		player->player_size.width,
		player->player_size.height
	);

	for (Rect tile : tiles)
	{
		if (player_rect.intersectsRect(tile)) 
		{
			player->velocity_x = 0;
			break;
		}
	}

	tiles.clear();

	if (player->velocity_y > 0) 
	{
		tiles = level->getCollisionTilesY(tmp, 1);
	}
	else if (player->velocity_y < 0)
	{
		tiles = level->getCollisionTilesY(tmp, -1);
	}

	player_rect.setRect(
		player->getBoundingBox().getMinX(),
		player->getBoundingBox().getMinY(),
		player->player_size.width,
		player->player_size.height
	);

	for (Rect tile : tiles)
	{

		if (tile.intersectsRect(player_rect)) 
		{
			if (player->velocity_y > 0) 
			{

				player->setPositionY(player->getPositionY() - player->velocity_y);

			}
			else 
			{

				player->setPositionY(tile.getMaxY());
				// if we hit the ground, mark us as grounded so we can jump
				player->grounded = true;
				player->jumping = false;

			}
			player->velocity_y = 0;
			break;

		}
		player->grounded = false;
	}

	// check for enemy collisions
	for (Sprite *tile : enemyList)
	{

		if (tile->getBoundingBox().intersectsRect(player_rect))
		{

			Point p = level->tileCoordinateToPosition(Point(10, 2));
			player->setPosition(p);
		}
	}

	player->updateState(delta);
	player->velocity_x = 0;

}


void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end())
		heldKeys.push_back(keyCode);
	

}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}

int GameScene::signum(float x)
{
	if (x > 0.0L)
		return 1.0L;
	else if (x < 0.0L)
		return -1.0L;
	else
		return 0.0L;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

GameScene::GameScene(void)
{
	setKeyboardEnabled(true);
	collidesX = false;
}
GameScene::~GameScene(void)
{
}
