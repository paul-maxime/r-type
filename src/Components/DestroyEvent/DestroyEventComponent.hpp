#ifndef DESTROYEVENTCOMPONENT_HPP_
#define DESTROYEVENTCOMPONENT_HPP_

#include <list>
#include <memory>
#include <functional>

#include "RType/ECS/AComponent.hpp"
#include "IDestroyEvent.hpp"

RTYPE_PLUGIN
class DestroyEventComponent : public rtype::ecs::AComponent, public IDestroyEvent
{
	RTYPE_COMPONENT

private:
	std::list<std::weak_ptr<std::function<void (rtype::ecs::GameObject&)>>> _callbacks;

public:
	virtual ~DestroyEventComponent() {}

	virtual void stop();

	virtual void subscribe(std::shared_ptr<std::function<void(rtype::ecs::GameObject&)>> fct);
};

#endif // !DESTROYEVENTCOMPONENT_HPP_
