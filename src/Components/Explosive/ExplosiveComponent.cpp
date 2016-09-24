#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "ExplosiveComponent.hpp"

RTYPE_COMPONENT_IMPL(ExplosiveComponent)

void ExplosiveComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_entity = file.getString("entity");

	if (file.hasField("position"))
	{
		rtype::ecs::file::Value position = file["position"];
		_position.x = position[0].asFloat();
		_position.y = position[1].asFloat();
	}
}

void ExplosiveComponent::stop()
{
	spawnExplosion();
}

void ExplosiveComponent::spawnExplosion()
{
	if (_entity.empty()) return;

	auto myTransform = gameObject().getComponent<ITransform>();
	if (!myTransform) return;

	const rtype::ecs::Vector3f& pos = myTransform->getAbsolutePosition();
	if (pos.x > 0.0f && pos.y > 0.0f && pos.x < 1024.0f && pos.y < 768.0f)
	{
		rtype::ecs::GameObject* explosion = gameEngine().createGameObject(_entity);
		auto newTransform = explosion->getComponent<ITransform>();
		if (newTransform)
		{
			newTransform->setPosition(pos + _position);
		}
	}
}
