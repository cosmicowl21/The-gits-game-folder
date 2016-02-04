//Author: James Walsh 
//Student Number: K00175707
#include "Projectile.h"//opens

Projectile* Projectile::projectile()
{
	Projectile* projectile = (Projectile*)Sprite::create("Projectile.png");
	if (projectile != NULL)
	{
		return projectile;
	}
	else {
		return NULL;
	}
}