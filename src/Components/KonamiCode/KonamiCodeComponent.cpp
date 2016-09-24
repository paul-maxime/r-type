#include <iostream>

#include "RType/ECS/GameEngine.hpp"
#include "Components/Player/IPlayerComponent.hpp"
#include "KonamiCodeComponent.hpp"

RTYPE_COMPONENT_IMPL(KonamiCodeComponent)

KonamiCodeComponent::KonamiCodeComponent()
{
	_it = 0;
	_code.push_back(rtype::ecs::IInput::key::Up);
	_code.push_back(rtype::ecs::IInput::key::Up);

	_code.push_back(rtype::ecs::IInput::key::Down);
	_code.push_back(rtype::ecs::IInput::key::Down);

	_code.push_back(rtype::ecs::IInput::key::Left);
	_code.push_back(rtype::ecs::IInput::key::Right);

	_code.push_back(rtype::ecs::IInput::key::Left);
	_code.push_back(rtype::ecs::IInput::key::Right);

	_code.push_back(rtype::ecs::IInput::key::B);
	_code.push_back(rtype::ecs::IInput::key::A);
}

void KonamiCodeComponent::update()
{
	if (!gameEngine().hasGraphics() || !gameObject().isLocal()) return;

	rtype::ecs::IInput::key		key;

	if (gameEngine().getInputs().onKeyDown(key))
	{
		if (key == _code[_it])
		{
			if (_it == 0)
				std::cout << "Cheat code begin :" << std::endl;
			_it++;
			std::cout << _it << " / 9" << std::endl;
		}
		else
			_it = 0;
	}
	if (_it >= _code.size())
	{
		std::cout << "Cheat code activated : A Thousand of Life and Damages" << std::endl;
		_it = 0;

		auto player = gameObject().getComponent<IPlayerComponent>();

		if (player)
		{
			player->setLives(100);
			player->setDamage(100);
		}
	}
}
