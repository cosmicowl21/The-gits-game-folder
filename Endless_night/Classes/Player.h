#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>
#include <string>

class Player
{
public:

	Player();
	Player(std::string, int);
	~Player();

	std::string username;
	int score;
};

#endif