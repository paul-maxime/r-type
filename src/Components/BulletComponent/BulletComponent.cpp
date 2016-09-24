#include "BulletComponent.hpp"
#include "Components/ShootableEnemy/IShootableEnemy.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/PlayerShip/IPlayerShip.hpp"
#include "RType/ECS/GameEngine.hpp"

RTYPE_COMPONENT_IMPL(BulletComponent)

void BulletComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_team = file.getInt("team");
	_damages = file.getInt("damage");
	_immortal = file.getBool("immortal");
}

void BulletComponent::onCollision(rtype::ecs::GameObject &obj)
{
	auto target = obj.getComponent<IShootableEnemy>();
	if (target)
	{
		if (target->team() != _team)
		{
			target->doDamage(_damages);
			if (!_immortal)
				gameObject().destroy();
		}
		return;
	}

	if (!_team)
	{
		auto force = obj.getComponent<AForce>();
		if (force)
		{
			gameObject().destroy();
			return;
		}

		auto player = obj.getComponent<IPlayerShip>();
		if (player && player->hit() && !_immortal)
		{
			gameObject().destroy();
		}
	}
}

void BulletComponent::setDamage(int8_t damage)
{
	_damages = damage;
}
