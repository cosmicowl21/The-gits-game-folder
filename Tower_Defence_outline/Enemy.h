#pragma once
#include <iostream>
#include<string>

using namespace std;

class Enemy
{
private:
	int health;
	int attack;
	string type;


public:
	Enemy();
	~Enemy();
};