#ifndef LASERBOSSCOMPONENT_HPP_
#define LASERBOSSCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/ColliderSystem/ICollider.hpp"

RTYPE_PLUGIN
class LaserBossComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	bool _laserFull;

public:
	virtual ~LaserBossComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void draw();
};

#endif // !LASERBOSSCOMPONENT_HPP_
