#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

//int Entity::attack()
//{
//	return 10;
//}

void Entity::takeDamage(int damage)
{
	health = health - attack();
}

bool Entity::isAlive()
{
	return (health > 0);

	return (health == 0) ? false : true;

	if (health == 0)
		return false;
	else
		return true;
}
