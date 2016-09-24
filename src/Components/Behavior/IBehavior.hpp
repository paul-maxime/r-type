#ifndef IBEHAVIOR_HPP_
#define IBEHAVIOR_HPP_

#include "RType/ECS/Vector2.hpp"

class IBehavior
{
public:
	virtual ~IBehavior() {}

	virtual void setTotalFollowSpeed(float) = 0;
	virtual void setSpeed(const rtype::ecs::Vector2f&) = 0;
	virtual void setSpeedX(float x) = 0;
	virtual void setSpeedY(float y) = 0;
	virtual rtype::ecs::Vector2f const & getSpeed() const = 0;

	virtual void setRotationSpeed(float speed) = 0;
	virtual float getRotationSpeed() const = 0;
};

#endif /* !IBEHAVIOR_HPP_ */
