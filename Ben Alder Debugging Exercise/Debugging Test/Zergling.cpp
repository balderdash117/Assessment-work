#include "Zergling.h"



Zergling::Zergling()
{
	health = 45;
}


Zergling::~Zergling()
{
}

int Zergling::attack()
{
	int damage = 10;
	return damage;
}

void Zergling::takeDamage(int damage)
{
	health -= damage;
	if (health < 0)
		health = 0;
}
