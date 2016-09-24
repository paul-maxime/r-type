#ifndef WEAPONS_COMPONENT_HPP_
#define WEAPONS_COMPONENT_HPP_

#include <functional>
#include <unordered_map>
#include "Components/Transform/ITransform.hpp"
#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "Components/Weapons/BulletSpawner/BulletSpawner.hpp"
#include "IWeapons.hpp"
#include "RType/ECS/Vector3.hpp"
#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class WeaponsComponent : public rtype::ecs::AComponent, public APlayerControllable, public BulletSpawner, public IWeapons
{
	RTYPE_COMPONENT

private:
	static const std::unordered_map< std::string, std::string > UPGRADES;
	static const std::unordered_map< std::string,
									 std::function<void (WeaponsComponent&,
										 const IPlayerInputs&)> > WEAPONS;

public:
	virtual ~WeaponsComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();

	virtual void upgrade();
	virtual void addSpeed(float speed);
	virtual void addDamage(int8_t damage);

private:
	void startAtkAnim();
	void stopAtkAnim();

private:
	void gun(const IPlayerInputs&);
	void doubleGun(const IPlayerInputs&);
	void tripleGun(const IPlayerInputs&);
	void sideGuns(const IPlayerInputs&);

private:
	rtype::ecs::Vector3f _offset;
	std::string _weapon;
	std::string _ammo;
	int8_t _damage;
	float _timer;
	float _cooldown;
	bool _upgrade;
	float _angle;
	bool _guided;
	float _bulletSpeed;
	bool _atkPressed;
};

#endif /* !WEAPONS_COMPONENT_HPP_ */
