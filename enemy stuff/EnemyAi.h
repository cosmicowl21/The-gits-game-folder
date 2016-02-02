/*

#ifndef ENEMY_AI_H
#define ENEMY_AI_H
enum
{
	KmoodSleep,
	KmoodSeek,
	kmoodAttack,
};

class AI :public Enemy
{

	
private:
	typedef Enemy super;
	typedef AI self;

protected:
	//the current mood of this AI
	int mood;

	//a timer  used in mood functions
	float timer;
	//when player is close enough, this object
	float wakeDistanceSQ;

	//return the amount if time this ai will sleep for
	virtual float sleepTime();
	//set new mood
	virtual void setMood(int newMood);
	//autimatically choose a new mood
	virtual void chooseMood();
	//returns true if ai can wake up
	virtual bool canWakeUp();

public:
	AI();
	virtual ~AI();

//allow the ai to think and move
	virtual void update(float delta);

	//run the sleep mood
	virtual void moodSleep(float delta);
	//run the seek mood(find the player)
	virtual void moodSeek(float delta);
	//run the attack mood 
	virtual void moodAttack(float delta);

}
#endif //EnemyAi

*/