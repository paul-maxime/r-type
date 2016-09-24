#ifndef ICOLLISION_HPP_
# define ICOLLISION_HPP_

# include "RType/ECS/GameObject.hpp"
# include "RType/ECS/Rect.hpp"

// To be inherited by components that have a collide method to be executed
class ICollision
{
public:
	virtual ~ICollision() {}

public:
	virtual void onCollision(rtype::ecs::GameObject &collidingObject) = 0;
};

#endif