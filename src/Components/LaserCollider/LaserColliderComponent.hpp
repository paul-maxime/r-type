#ifndef LASERCOLLIDERCOMPONENT_HPP_
#define LASERCOLLIDERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/ColliderSystem/ICollider.hpp"
#include "Components/ColliderSystem/ICollision.hpp"
#include "Components/PlayerShip/IPlayerShip.hpp"
#include "Components/ShootableEnemy/IShootableEnemy.hpp"

RTYPE_PLUGIN
class LaserColliderComponent : public rtype::ecs::AComponent, public ICollision
{
	RTYPE_COMPONENT

private:

public:
	virtual ~LaserColliderComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void draw();

	virtual void onCollision(rtype::ecs::GameObject &);
};

#endif // !LASERCOLLIDERCOMPONENT_HPP_
