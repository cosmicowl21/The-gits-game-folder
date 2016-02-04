//Author: James Walsh 
//Student Number: K00175707
#include "Tower.h"
#include "GameManager.h"


Tower* PowerFullTower::tower()
{
	Tower* tower = Tower::create();
	tower->sprite = Sprite::create("icetower.png");//image for the tower
	tower->setScale(0.5);
	tower->addChild(tower->sprite, 0);
	tower->range = 200;
	tower->schedule(schedule_selector(towerLogic), 0.2);
	return tower;
}

bool PowerFullTower::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void PowerFullTower::towerLogic(float dt)
{
	this->target = this->getClosestTarget();
	if (this->target != NULL)
	{
		Point shootVector = this->target->getPosition() - this->getPosition();
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

		float rotateSpeed = 0.5 / M_PI;
		float rotateDuration = fabs(shootAngle * rotateSpeed);

		this->runAction(Sequence::create(RotateTo::create(rotateDuration, cocosAngle), CallFunc::create(this, callfunc_selector(PowerFullTower::finishFiring)), NULL));
	}
}

Creep* Tower::getClosesTarget()
{
	Creep *closestCreep = NULL;
	double maxDistance = 99999;//this has to be bigger than the range
	GameManager *g = GameManager::getGame();

	for each(Sprite *target in g->targets)
	{
		Creep *creep = (Creep*)target;
		double currentDistance = ccpDistance(this->getPosition(), creep->getPosition());

		if (currentDistance < maxDistance)
		{
			closestCreep = creep;
			maxDistance = currentDistance;
		}
	}
	if (maxDistance < this->range)
	{
		return closestCreep;
	}

	return NULL;
}

void PowerFullTower::finishFiring()
{
	GameManager *g = GameManager::getGame();
	if (this->target  != NULL && this->target->currentHP > 0 && this->target->currentHP < 1000)
	{
		this->nextProjectile = Projectile::projectile();
		this->nextProjectile->setPosition(this->getPosition());
		this->getParent()->addChild(this->nextProjectile, 1);
		g->projectiles.pushBack(this->nextProjectile);

		float delta = 1.0f;
		Point shootVector = -(this->target->getPosition() - this->getPosition());
		Point normalizedShootVector = ccpNormalize(shootVector);
		Point overshotVector = normalizedShootVector * 320;
		Point offscreenPoint = (this->getPosition() - overshotVector);

		this->nextProjectile->runAction(Sequence::create(MoveTo::create(delta, offscreenPoint), CallFunc::create(this, callfunc_selector(PowerFullTower::creepMoveFinished)), NULL));

		this->nextProjectile->setTag(2);

		this->nextProjectile = NULL;

	}
}

void PowerFullTower::creepMoveFinished(Node* sender)
{
	GameManager * g = GameManager::getGame();
	Sprite *sprite = (Sprite *)sender;
	this->getParent()->removeChild(sprite, true);

	g->projectiles.eraseObject((Projectile*)sprite);
}


	
