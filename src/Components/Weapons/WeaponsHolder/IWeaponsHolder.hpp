#ifndef IWEAPONS_HOLDER_HPP_
#define IWEAPONS_HOLDER_HPP_

#include <string>
#include <vector>
#include "RType/ECS/GameEngine.hpp"
#include "Components/Force/AForce.hpp"

class IWeaponsHolder
{
public:
	virtual ~IWeaponsHolder() {}

	virtual void addWeapon(const std::string& weapon, AForce* force = NULL) = 0;

	virtual void upgrade() = 0;
	virtual void addSpeed(float speed) = 0;
	virtual void addDamage(int8_t damage) = 0;
	virtual bool hasSpace() const = 0;
};

#endif /* !IWEAPONS_HOLDER_HPP_ */
