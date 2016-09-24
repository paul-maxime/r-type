#include "RType/ECS/GameEngine.hpp"
#include "LaserColliderComponent.hpp"

RTYPE_COMPONENT_IMPL(LaserColliderComponent)

void LaserColliderComponent::loadFile(const rtype::ecs::file::Value&)
{
}

void LaserColliderComponent::start()
{
}

void LaserColliderComponent::update()
{

}

void LaserColliderComponent::draw()
{
}

void LaserColliderComponent::onCollision(rtype::ecs::GameObject& collision)
{
	if (collision.name() == "boss")
		return;
	auto player = collision.getComponent<IPlayerShip>();
	if (player && player->hit())
		return;

	auto enemy = collision.getComponent<IShootableEnemy>();
	if (enemy)
	{
		enemy->doDamage(100);
	}
}
