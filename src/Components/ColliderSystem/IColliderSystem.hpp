#ifndef ICOLLIDERSYSTEM_HPP_
# define ICOLLIDERSYSTEM_HPP_

#include "RType/ECS/GameObject.hpp"

class IColliderSystem
{
public:
	virtual ~IColliderSystem() {}

public:
	virtual void subscribeCollision(rtype::ecs::GameObject *) = 0; // Each time we create a colliderComponent it subscribes to the ColliderSystem
	virtual void unsubscribeCollision(rtype::ecs::GameObject *) = 0; // Each time we delete a colliderComponent it unsubscribes to the ColliderSystem
};

#endif