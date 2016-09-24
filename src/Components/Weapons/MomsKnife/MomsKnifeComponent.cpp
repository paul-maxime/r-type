#include <iostream>
#include "RType/ECS/GameEngine.hpp"
#include "RType/ECS/GameObject.hpp"
#include "Components/Behavior/IBehavior.hpp"
#include "Components/ShootableEnemy/IShootableEnemy.hpp"
#include "MomsKnifeComponent.hpp"

const float MomsKnifeComponent::MAX_LOAD = 1000;

RTYPE_COMPONENT_IMPL(MomsKnifeComponent)

void MomsKnifeComponent::loadFile(const rtype::ecs::file::Value& file)
{
	if (file.hasField("offset"))
	{
		auto offset = file["offset"];
		if (offset.size() >= 1)
			_offset.x = offset[0].asFloat();
		if (offset.size() >= 2)
			_offset.y = offset[1].asFloat();
		if (offset.size() >= 3)
			_offset.z = offset[2].asFloat();
	}
	_damage = file.getInt("basic_damage");
}

void MomsKnifeComponent::start()
{
	_atkPressed = false;
	_attacking = false;
	_speed = 0;

	auto transform = gameObject().getComponent<ITransform>();
	if (transform)
	{
		transform->setPosition(_offset);
	}
}

void MomsKnifeComponent::update()
{
	if (!gameObject().isLocal()) return;

	auto transform = gameObject().getComponent<ITransform>();

	if (transform && transform->hasParent())
	{
		if (_attacking)
			attacking(*transform);
		else
			loading();
	}
}


void MomsKnifeComponent::onCollision(rtype::ecs::GameObject &obj)
{
	std::shared_ptr<IShootableEnemy> target = obj.getComponent<IShootableEnemy>();

	if (target)
	{
		target->doDamage(_damage + getPlayer()->getDamage());
	}
}

void MomsKnifeComponent::addDamage(int8_t damage)
{
	_damage += damage;
}

void MomsKnifeComponent::attacking(ITransform& transform)
{
	auto b = gameObject().getComponent<IBehavior>();

	if (b)
	{
		const rtype::ecs::Vector3f& pos = transform.getPosition();

		if (pos.x <= _offset.x && pos.y <= _offset.y && _speed <= 0)
		{
			_attacking = false;
			_speed = 0;
		}
		else
			_speed -= 1500 * gameEngine().getElapsedTime();
		b->setSpeed(rtype::ecs::Vector2f(_speed, 0));
		rtype::ecs::Vector3f reset(pos);

		if (pos.x < _offset.x)
			reset.x = _offset.x;
		if (pos.y < _offset.y)
			reset.y = _offset.y;
		transform.setPosition(reset);
	}
}

void MomsKnifeComponent::loading()
{
	auto inputs = getInputs();
	if (inputs)
	{
		if (inputs->isPressed(IPlayerInputs::ATTACK))
		{
			_atkPressed = true;
			_speed += 2000 * gameEngine().getElapsedTime();
			if (_speed > MAX_LOAD)
				_speed = MAX_LOAD;
		}
		else if (_atkPressed)
		{
			_attacking = true;
			_atkPressed = false;
		}
	}
}

void MomsKnifeComponent::addSpeed(int8_t speed)
{
	_speed += speed;
}