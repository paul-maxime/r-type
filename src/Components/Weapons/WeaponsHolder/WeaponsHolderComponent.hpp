#ifndef WEAPONS_HOLDER_COMPONENT_HPP_
#define WEAPONS_HOLDER_COMPONENT_HPP_

#include <string>
#include <vector>
#include "RType/ECS/AComponent.hpp"
#include "IWeaponsHolder.hpp"

RTYPE_PLUGIN
class WeaponsHolderComponent : public rtype::ecs::AComponent, public IWeaponsHolder
{
	RTYPE_COMPONENT

private:
	static const std::string DEFAULT_WEAPON;

	struct forces
	{
		AForce* force;
		std::string weaponName;
		rtype::ecs::GameObject* weapon;
	};

public:
	virtual ~WeaponsHolderComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void update();
	virtual void start();
	virtual void stop();

	virtual void addWeapon(const std::string& weapon, AForce* force = NULL);

	virtual void upgrade();
	virtual void addSpeed(float speed);
	virtual void addDamage(int8_t damage);

	virtual bool hasSpace() const;

private:
	std::string _defaultWeapon;
	unsigned int _max;
	bool release;

	std::vector< forces > _weapons;
};

#endif /* !WEAPONS_HOLDER_COMPONENT_HPP_ */
