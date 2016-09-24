#include "EnnemyCollision.hpp"

#include <iostream>

RTYPE_COMPONENT_IMPL(EnnemyCollision)

EnnemyCollision::~EnnemyCollision()
{
}

void EnnemyCollision::onCollision(rtype::ecs::GameObject &collision)
{
	if (collision.name() == "PlayerShip")
	{
		std::cout << "Bzbbbzbbzzzz TK01 hit by humans !" << std::endl;
		collision.destroy();
	}

	if (collision.name() == "PlayerBullet")
	{
		gameObject().destroy();
	}
}