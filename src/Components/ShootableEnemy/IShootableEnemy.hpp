#ifndef ISHOOTABLEENEMY_HPP_
# define ISHOOTABLEENEMY_HPP_

# include "RType/ECS/AComponent.hpp"
# include "Components/ColliderSystem/ICollision.hpp"

class IShootableEnemy
{
public:

	virtual ~IShootableEnemy() {};

	virtual int8_t team() const = 0;
	virtual void doDamage(int8_t) = 0;
	virtual int16_t life() const = 0;
};

#endif
