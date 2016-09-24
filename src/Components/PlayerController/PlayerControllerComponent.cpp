#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/PlayerInputs/IPlayerInputs.hpp"
#include "PlayerControllerComponent.hpp"

RTYPE_COMPONENT_IMPL(PlayerControllerComponent)

void PlayerControllerComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_speed = file.getFloat("speed", 100.0f);
}

void PlayerControllerComponent::update()
{
	auto  t = gameObject().name();
	if (!gameObject().isLocal()) return;

	auto transform = gameObject().getComponent<ITransform>();
	auto inputs = getInputs();
	if (transform && inputs)
	{
		rtype::ecs::Vector3f movement;

		if (inputs->isPressed(IPlayerInputs::MOVE_RIGHT))
			movement.x += 1.0f;
		if (inputs->isPressed(IPlayerInputs::MOVE_LEFT))
			movement.x -= 1.0f;
		if (inputs->isPressed(IPlayerInputs::MOVE_UP))
			movement.y -= 1.0f;
		if (inputs->isPressed(IPlayerInputs::MOVE_DOWN))
			movement.y += 1.0f;

		movement = movement.normalize() * gameEngine().getElapsedTime() * _speed;

		transform->move(movement);

		rtype::ecs::Vector3f position = transform->getPosition();

		if (position.x < 0.0f)
			position.x = 0.0f;
		if (position.x > 1024.0f - 40.0f)
			position.x = 1024.0f - 40.0f;
		if (position.y < 0.0f)
			position.y = 0.0f;
		if (position.y > 768.0 - 48.0f)
			position.y = 768.0 - 48.0f;

		transform->setPosition(position);
	}
}

void PlayerControllerComponent::addSpeed(float speed)
{
	_speed += speed;
}