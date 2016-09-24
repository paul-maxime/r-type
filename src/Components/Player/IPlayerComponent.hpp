#ifndef IPLAYERCOMPONENT_HPP_
#define IPLAYERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

class IPlayerComponent
{

public:
	virtual ~IPlayerComponent() {}

	virtual void addLife() = 0;
	virtual int8_t getDamage() = 0;
	virtual void setDamage(int8_t) = 0;
	virtual void addSpeed(float) = 0;
	virtual void setLives(int8_t) = 0;
};

#endif // !IPLAYERCOMPONENT_HPP_
