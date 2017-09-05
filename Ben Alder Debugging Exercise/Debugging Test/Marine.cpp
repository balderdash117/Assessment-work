#include "Marine.h"



Marine::Marine()
{
	health = 50;
}


Marine::~Marine()
{
}

int Marine::attack()
{
	int damage = 15;
	return damage;
}

void Marine::takeDamage(int damage)
{
	health -= damage;
}
