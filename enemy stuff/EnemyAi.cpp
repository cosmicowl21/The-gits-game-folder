/*
#include "EnemyAi.h"

const float KTimerUP = -9999.0f;
const float KTimerUP = -9999.0f;



AI::AI()
{
	mood = kMoodSleep;
	timer = kTimerUp;
	wakeDistanceSQ = 400.0f * 300.0f;
}

AI::~AI()
{
}

float AI::sleepTime()
{
	// return the amount of time this AI will sleep for;
	// this function is in place so different types of sub classes
	// can sleep for different amounts of time
	return 0.5f;
}

void AI::setMood(int newMood)
{
	// set new Mood
	mood = newMood;

	// reset the timer so the mood initializes itself
	timer = kTimerUp;
}

void AI::chooseMood()
{
	// this is the default chooseMood method
	// override it to implement different enemy personalities

	// choose between seeking and sleeping
	this->setMood(this->canWakeup() ? kMoodSeek : kMoodSleep);
}

bool AI::canWakeup()
{
	// can wake if player is alive and is close enough
	Player& player = this->getPlayer(); // inherited from LevelObject

	// note that player distance is saved for later use
	float playerDistanceSQ = this->distanceSQ(player.getPosition());

	return (player.isAlive() && playerDistanceSQ < wakeDistanceSQ);
}

void AI::update(float delta)
{
	super::update(delta);

	if (this->isAlive())
	{
		// count down the timer
		if (timer != kTimerUp)
			timer -= delta;

		// perform current mood
		switch (mood)
		{
		case kMoodSleep: this->moodSleep(delta); break;
		case kMoodSeek: this->moodSeek(delta); break;
		case kMoodAttack: this->moodAttack(delta); break;
		}
	}
}

void AI::moodSleep(float delta)
{
	// starting sleep mood...
	if (timer == kTimerUp)
	{
		timer = this->sleepTime() + (this->sleepTime() * CCRANDOM_0_1());
		this->sprite->stopAllActions();
		this->animate("sleep", kActionSleep);
	}

	// wake up?
	else if (timer <= 0.0f)
		this->chooseMood();
}

void AI::moodSeek(float delta)
{
	// starting seek mood...
	if (timer == kTimerUp)
		timer = 1.0f;

	// timer up
	else if (timer <= 0.0f)
		this->chooseMood();
}

void AI::moodAttack(float delta)
{
	// starting attack mood
	if (timer == kTimerUp)
		timer = 1.0f;

	// timer up
	else if (timer <= 0.0f)
		this->chooseMood();
}

*/