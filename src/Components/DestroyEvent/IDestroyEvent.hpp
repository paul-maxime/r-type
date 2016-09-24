#ifndef IDESTROYEVENT_HPP_
#define IDESTROYEVENT_HPP_

#include <memory>
#include <functional>

#include "RType/ECS/GameObject.hpp"

class IDestroyEvent
{
public:
	virtual ~IDestroyEvent() {}

	virtual void subscribe(std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>> fct) = 0;
};

#endif // IDESTROYEVENT_HPP_
