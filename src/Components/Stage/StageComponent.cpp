#include <iostream>

#include "Components/DestroyEvent/IDestroyEvent.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/TextRenderer/ITextRenderer.hpp"
#include "Components/Behavior/IBehavior.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "StageComponent.hpp"

RTYPE_COMPONENT_IMPL(StageComponent)

void StageComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_name = file.getString("name");
	auto actions = file["actions"];
	_actions.reserve(actions.size());
	for (size_t i = 0; i < actions.size(); ++i)
	{
		auto spawn = actions[i];
		StageAction action;
		action.entity = spawn[0].asString();
		action.x = spawn[1].asFloat();
		action.y = spawn[2].asFloat();
		action.time = spawn[3].asFloat();
		if (spawn.size() > 4)
		{
			action.speedX = spawn[4].asFloat();
			action.speedY = spawn[5].asFloat();
			action.hasSpeed = true;
		}
		else
		{
			action.speedX = 0.0f;
			action.speedY = 0.0f;
			action.hasSpeed = false;
		}
		_actions.push_back(std::move(action));
	}
	_nextStage = file.getString("next");
	_currentAction = 0;
	_currentTime = 0.0f;
}

void StageComponent::start()
{
	gameObject().name("Stage");
	auto renderer = gameObject().getComponent<ITextRenderer>();
	if (renderer)
	{
		renderer->setText(_name);
	}
	_onEntityDestroy = std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>>
		(new std::function<void (rtype::ecs::GameObject&)>
			(std::bind(&StageComponent::onEntityDestroy, this, std::placeholders::_1)));
}

void StageComponent::update()
{
	if (!gameObject().isLocal()) return;

	_currentTime += gameEngine().getElapsedTime();

	bool spawned = true;
	while (spawned && _currentAction < _actions.size())
	{
		const StageAction& current = _actions[_currentAction];

		spawned = false;
		if ((current.time >= 0 && _currentTime > current.time) ||
			(current.time < 0 && _aliveEntities.empty()))
		{
			if (current.time < 0)
				_currentTime = 0;
			else
				_currentTime -= current.time;
			++_currentAction;
			spawned = true;

			rtype::ecs::Vector3f pos(current.x * 1024.0f / 100.0f,
				current.y * 768.0f / 100.0f,
				0);

			rtype::ecs::GameObject* obj = gameEngine().createGameObject(current.entity);

			auto transform = obj->getComponent<ITransform>();
			if (transform)
				transform->setPosition(pos);

			auto behavior = obj->getComponent<IBehavior>();
			if (behavior && current.hasSpeed)
				behavior->setSpeed(rtype::ecs::Vector2f(current.speedX, current.speedY));

			auto event = obj->getComponent<IDestroyEvent>();
			if (event)
			{
				_aliveEntities.push_back(obj);
				event->subscribe(_onEntityDestroy);
			}
		}
	}

	if (_currentAction == _actions.size() && _aliveEntities.empty())
	{
		if (!_nextStage.empty())
			gameEngine().createGameObject(_nextStage);
		gameObject().destroy();
	}
}

const std::string& StageComponent::name() const
{
	return _name;
}

void StageComponent::onEntityDestroy(rtype::ecs::GameObject& sender)
{
	_aliveEntities.remove(&sender);
}
