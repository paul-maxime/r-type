#include <iostream>
#include "RType/ECS/GameEngine.hpp"
#include "LaserBossComponent.hpp"

RTYPE_COMPONENT_IMPL(LaserBossComponent)

void LaserBossComponent::loadFile(const rtype::ecs::file::Value&)
{
}

void LaserBossComponent::start()
{
	auto t = gameObject().getComponent<ITransform>();
	auto c = gameObject().getComponent<ICollider>();
	if (!t)
		throw std::runtime_error("cannot use BossLaser without a Transform component");
	if (!c)
		throw std::runtime_error("cannot use BossLaser without a Collider component");
	_laserFull = false;
	gameObject().layer(-1);
}

void LaserBossComponent::update()
{
	auto & t = *(gameObject().getComponent<ITransform>());
	auto deltaT = gameEngine().getElapsedTime();

	if (t.getSize().y < 0.2 && !_laserFull)
	{
		t.setPosition(t.getPosition() - rtype::ecs::Vector2f(0.f, 10.f * deltaT));
		t.setSize(t.getSize() + rtype::ecs::Vector2f(0.f, 0.1f * deltaT));
	}
	else if (t.getSize().y > 0.1)
	{
		t.setPosition(t.getPosition() + rtype::ecs::Vector2f(0.f, 20.f * deltaT));
		t.setSize(t.getSize() - rtype::ecs::Vector2f(0.f, 0.2f * deltaT));
		_laserFull = true;
	}
	else
		gameObject().destroy();
}

void LaserBossComponent::draw()
{
}
