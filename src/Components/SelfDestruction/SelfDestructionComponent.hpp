#ifndef SELFDESTRUCTIONCOMPONENT_HPP_
#define SELFDESTRUCTIONCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class SelfDestructionComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

public:
	virtual ~SelfDestructionComponent() {}

	virtual void update();
};

#endif // !SELFDESTRUCTIONCOMPONENT_HPP_
