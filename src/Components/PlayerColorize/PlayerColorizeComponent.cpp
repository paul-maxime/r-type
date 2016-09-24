#include <iostream>
#include "RType/ECS/GameEngine.hpp"
#include "PlayerColorizeComponent.hpp"

RTYPE_COMPONENT_IMPL(PlayerColorizeComponent)

void PlayerColorizeComponent::loadFile(const rtype::ecs::file::Value&)
{

}

void PlayerColorizeComponent::start()
{
}

void PlayerColorizeComponent::update()
{
}

uint8_t PlayerColorizeComponent::sprite(size_t id, size_t size)
{
	if (size <= 1)
		return 0;
	if (_taken.find(id) != _taken.end())
		return _taken[id];

	for (auto it = _taken.begin(); it != _taken.end();)
	{
		auto tmp = it;
		tmp++;
		auto & instance = *it;
		if(std::find_if(gameEngine().gameObjects().begin(),
				gameEngine().gameObjects().end(),
				[&instance](std::shared_ptr<rtype::ecs::GameObject> const & obj)
				{
					if (obj->instanceId() == instance.first)
						return true;
					return false;
				}) == gameEngine().gameObjects().end())
			_taken.erase(instance.first);
		it = tmp;
	}

	uint8_t i;
	for (i = 1; i < size; i++)
	{
		if (std::find_if(_taken.begin(),
				_taken.end(),
				[&i](std::pair<size_t, size_t> const & e)
				{
					if (e.second == i)
						return true;
					return false;
				}) == _taken.end())
			break;
	}
	if (i >= size)
		i = 0;
	_taken[id] = i;
	return (i);
}

void PlayerColorizeComponent::draw()
{
}
