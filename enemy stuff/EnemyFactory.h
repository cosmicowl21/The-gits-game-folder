#ifndef  ENEMY_FACTORY_H
#define  ENEMY_FACTORY_H
#include <iostream>

#include "cocos2d.h"
// class file for abstract Enemy factory
class EnemyFactory
{
public:
	EnemyFactory(){};
	~EnemyFactory(){};
	void init();
	virtual void draw() = 0;
	virtual void update() = 0;
private:

};

class Enemies : public EnemyFactory
{
public:
	void draw(){
		std::cout << "Enemy  has Spawned" << std::endl;

	}
	void update(){
		std::cout << "Enemy has moved postion" << std::endl;
	}

};

class Bossfactory : public EnemyFactory
{
public:
	void draw(){
		std::cout << "Boss has spawned" << std::endl;
	}
	void update(){
		std::cout << "Boss has moved postion" << std::endl;
	}

};



class Factory{
public:
	virtual EnemyFactory* ghoul() = 0;
	virtual EnemyFactory* deathclaw() = 0;

};

class CharacterFactory : public Factory
{
public:
	EnemyFactory* ghoul(){
		return new Enemies;
	}
	EnemyFactory* deathclaw()
	{
		return new Bossfactory;
	}
};




#endif //ENEMY_FACTORY_H

