//Author: James Walsh 
//Student Number: K00175707
#include "GameManager.h"

USING_NS_CC;
GameManager* GameManager::g_pInstance;
GameManager* GameManager::getGame()
{

	if (g_pInstance == NULL)
	{
		g_pInstance = new GameManager();
	}

	return g_pInstance;
}