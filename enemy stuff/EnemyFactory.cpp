#include "EnemyFactory.h"
#include <vector>
using namespace std;
USING_NS_CC;
// enemy factory moved to gameMaager class
void EnemyFactory::init()
{
	Factory* factory = new CharacterFactory;
	vector<EnemyFactory*> characters;
	characters.push_back(factory->ghoul());
	characters.push_back(factory->deathclaw());


	for (int i = 0; i < characters.size(); i++)
	{
		characters[i]->draw();

	}
	cin.get();
}