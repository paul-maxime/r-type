#ifndef WINDOWHANDLERCOMPONENT_HPP_
#define WINDOWHANDLERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class WindowHandlerComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	float _escapeTime;

public:
	virtual ~WindowHandlerComponent() {};
	virtual void start();
	virtual void update();
};

#endif // WINDOWHANDLERCOMPONENT_HPP_
