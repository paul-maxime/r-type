#include <stdexcept>

#include "RType/ECS/GameEngine.hpp"
#include "RType/System/Random.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "Components/Behavior/IBehavior.hpp"
#include "Components/Transform/ITransform.hpp"
#include "AsteroidComponent.hpp"

RTYPE_COMPONENT_IMPL(AsteroidComponent)

void AsteroidComponent::loadFile(const rtype::ecs::file::Value& file)
{
	if (!file.hasField("sprites"))
		throw std::runtime_error("Asteroid component with no sprites");

	auto sprites = file["sprites"];
	if (sprites.size() < 1 || sprites.size() > 100)
		throw std::runtime_error("Asteroid component with invalid sprites size");

	for (size_t i = 0; i < sprites.size(); ++i)
		_sprites.push_back(sprites[i].asString());

	_child = file.getString("child");

	_index = -1;
}

void AsteroidComponent::start()
{
	if (!gameObject().isLocal()) return;

	if (_index < 0)
	{
		setIndex(static_cast<int8_t>(rtype::system::random::next(_sprites.size())));
	}

	auto behavior = gameObject().getComponent<IBehavior>();
	if (behavior)
	{
		behavior->setRotationSpeed(static_cast<float>(rtype::system::random::next(-180, 180)));
	}
}

void AsteroidComponent::stop()
{
	if (_child.empty() || !gameObject().isLocal()) return;

	for (size_t i = 0; i < 4; ++i)
	{
		rtype::ecs::GameObject* child = gameEngine().createGameObject(_child);
		auto asteroid = child->getComponent<IAsteroid>();
		if (asteroid)
			asteroid->setIndex(_index);
		auto behavior = child->getComponent<IBehavior>();
		if (behavior)
		{
			behavior->setSpeed(rtype::ecs::Vector2f(
					static_cast<float>(rtype::system::random::next(-300, 300)),
					static_cast<float>(rtype::system::random::next(-200, 200))
					));
		}
		auto self = gameObject().getComponent<ITransform>();
		auto transform = child->getComponent<ITransform>();
		if (self && transform)
		{
			transform->setPosition(self->getPosition());
		}
	}
}

void AsteroidComponent::serialize(rtype::system::BinaryWriter& writer)
{
	writer << _index;
}

void AsteroidComponent::unserialize(rtype::system::BinaryReader& reader)
{
	int8_t index;
	reader >> index;
	if (index != _index)
		setIndex(index);
}

void AsteroidComponent::setIndex(int8_t index)
{
	if (index != _index && index >= 0 && static_cast<size_t>(index) < _sprites.size())
	{
		_index = index;
		auto renderer = gameObject().getComponent<ISpriteRenderer>();
		if (renderer)
		{
			renderer->setSprite(_sprites[static_cast<size_t>(index)], rtype::ecs::IntRect());
		}
	}
}
