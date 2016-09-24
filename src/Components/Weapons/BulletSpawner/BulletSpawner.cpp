#include <iostream>
#include <cmath>
#include "Components/Transform/ITransform.hpp"
#include "Components/Behavior/IBehavior.hpp"
#include "Components/BulletComponent/IBullet.hpp"
#include "BulletSpawner.hpp"

rtype::ecs::GameObject* BulletSpawner::createBullet(
	rtype::ecs::GameEngine& engine, rtype::ecs::GameObject& obj, const std::string& bullet,
	float speed, float angle, int8_t damage, float rotate, const rtype::ecs::Vector2f& offset)
{
	auto g = engine.createGameObject(bullet);

	if (g)
	{
		move(obj, *g, offset);
		setSpeed(*g, speed, angle, rotate);

		auto b = g->getComponent<IBullet>();
		if (b && damage > 0)
		{
			b->setDamage(damage);
		}
	}
	return (g);
}

void BulletSpawner::move(rtype::ecs::GameObject& obj, rtype::ecs::GameObject& bullet,
						 const rtype::ecs::Vector2f& offset)
{
	auto t = bullet.getComponent<ITransform>();
	auto self = obj.getComponent<ITransform>();

	if (t)
	{
		if (self)
		{
			rtype::ecs::Vector3f pos = self->getAbsolutePosition();
			rtype::ecs::Vector2f size1 = self->getSize();
			rtype::ecs::Vector2f size2 = t->getSize();

			pos.x += (size1.x > size2.x ? (size1.x - size2.x) : (size2.x - size1.x)) / 2;
			pos.y += (size1.y > size2.y ? (size1.y - size2.y) : (size2.y - size1.y)) / 2;
			t->setPosition(pos + offset);
		}
	}
}

void BulletSpawner::setSpeed(rtype::ecs::GameObject& bullet, float speed, float angle, float rotate)
{
	auto b = bullet.getComponent<IBehavior>();
	auto t = bullet.getComponent<ITransform>();

	angle = fmodf(angle, 360);
	if (angle < 0)
		angle = 360 + angle;
	if (b)
	{
		float ang = ((angle < 90 && angle >= 0) || (angle >= 180 && angle < 270) ?
					 fmodf(angle, 90) : (angle < 180 ? 180 - angle : 360 - angle));
		int x = (angle >= 90 && angle <= 270 ? -1 : 1), y = (angle >= 0 && angle <= 180 ? -1 : 1);
		float vx = std::cos(ang * 3.14159265f / 180.f), vy = std::sin(ang * 3.14159265f / 180.f);

		float norme = std::sqrt(vx * vx + vy * vy);
		b->setSpeed(rtype::ecs::Vector2f(vx / norme * speed * x,
										 vy / norme * speed * y));
		b->setTotalFollowSpeed(speed);
		if (t && rotate)
			t->rotate(360 - angle);
	}
}
