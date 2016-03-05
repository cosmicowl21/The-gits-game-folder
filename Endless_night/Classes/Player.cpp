#include "Player.h"

Player::Player(std::string n, int s)
{
	username = n;
	score = s;
}

Player::Player()
{
	username = "";
	score = 0;
}

Player::~Player()
{
}