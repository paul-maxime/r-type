#ifndef ICOLLIDER_HPP_
# define ICOLLIDER_HPP_

# include "RType/ECS/GameObject.hpp"
# include "RType/ECS/Rect.hpp"

//Basic interface for ColliderComponent. It is used for the colliderSystem
class ICollider
{
public:
	virtual ~ICollider() {}

public:
	virtual const std::list<rtype::ecs::Rect<float>>& getHitbox() const = 0;
};

#endif
