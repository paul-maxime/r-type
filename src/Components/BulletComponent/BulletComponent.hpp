#ifndef BULLETCOMPONENT_HPP_
#define BULLETCOMPONENT_HPP_

#include <string>

#include "RType/ECS/AComponent.hpp"
#include "Components/ColliderSystem/ICollision.hpp"
#include "IBullet.hpp"
#include "Components/Force/AForce.hpp"

RTYPE_PLUGIN
class BulletComponent : public rtype::ecs::AComponent, public IBullet, public ICollision
{
	RTYPE_COMPONENT

private:
	int8_t _team;
	int8_t _damages;
	bool _immortal;

public:
	virtual void loadFile(const rtype::ecs::file::Value& file);
	virtual void onCollision(rtype::ecs::GameObject &);

	virtual void setDamage(int8_t damage);
};

#endif // BULLETCOMPONENT_HPP_
