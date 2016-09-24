#include <cmath>

#include "RType/ECS/GameEngine.hpp"
#include "RType/System/Random.hpp"
#include "AsteroidSpawnerComponent.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/Behavior/IBehavior.hpp"

RTYPE_COMPONENT_IMPL(AsteroidSpawnerComponent)

void AsteroidSpawnerComponent::loadFile(const rtype::ecs::file::Value& file)
{
	auto models = file["models"];

	if (models.size() < 1 || models.size() > 100)
		throw std::runtime_error("AsteroidSpawner with invalid models size");

	for (size_t i = 0; i < models.size(); ++i)
		_models.push_back(models[i].asString());

	_minDelay = file.getFloat("minDelay");
	_maxDelay = file.getFloat("maxDelay");
}

void AsteroidSpawnerComponent::start()
{
	_nextDelay = rtype::system::random::next(_minDelay, _maxDelay);
}

void AsteroidSpawnerComponent::update()
{
	if (!gameObject().isLocal()) return;

	_nextDelay -= gameEngine().getElapsedTime();
	if (_nextDelay < 0)
	{
		spawnAsteroid();
		_nextDelay = rtype::system::random::next(_minDelay, _maxDelay);
	}
}

void AsteroidSpawnerComponent::spawnAsteroid()
{
	std::string entity = _models[rtype::system::random::next(_models.size())];

	rtype::ecs::GameObject* obj = gameEngine().createGameObject(entity);

	auto transform = obj->getComponent<ITransform>();
	auto behavior = obj->getComponent<IBehavior>();

	if (!transform || !behavior)
		return;

	rtype::ecs::Vector2f speed(
		rtype::system::random::next(-300.0f, 300.0f),
		rtype::system::random::next(-200.0f, 200.0f));

	if (std::abs(speed.x) < 20.0f)
		speed.x = (speed.x < 0 ? speed.x - 20.0f : speed.x + 20.0f);
	if (std::abs(speed.y) < 20.0f)
		speed.y = (speed.y < 0 ? speed.y - 20.0f : speed.y + 20.0f);

	rtype::ecs::Vector3f pos;

	if (rtype::system::random::next(0, 2))
	{
		pos.x = -128.0f + rtype::system::random::next(0.0f, 1024.0f + 256.0f);
		pos.y = (speed.y > 0 ? -126.0f : 768.0f + 126.0f);
	}
	else
	{
		pos.x = (speed.x > 0 ? -126.0f : 1024.0f + 126.0f);
		pos.y = -128.0f + rtype::system::random::next(0.0f, 768.0f + 256.0f);
	}

	transform->setPosition(pos);
	behavior->setSpeed(speed);
}
