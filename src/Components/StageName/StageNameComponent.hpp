#ifndef STAGENAMECOMPONENT_HPP_
#define STAGENAMECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class StageNameComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	float _duration;

public:
	virtual ~StageNameComponent() {}

	virtual void start();
	virtual void update();
};

#endif // !STAGENAMECOMPONENT_HPP_
