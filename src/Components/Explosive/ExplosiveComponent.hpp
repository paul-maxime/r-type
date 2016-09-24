#ifndef EXPLOSIVECOMPONENT_HPP_
#define EXPLOSIVECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class ExplosiveComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::string _entity;
	rtype::ecs::Vector2f _position;

public:
	virtual ~ExplosiveComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void stop();

private:
	void spawnExplosion();
};

#endif // !EXPLOSIVECOMPONENT_HPP_
