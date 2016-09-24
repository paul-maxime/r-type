#include <iostream>
#include "Components/Transform/ITransform.hpp"
#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "Components/Weapons/Weapons/IWeapons.hpp"
#include "WeaponsHolderComponent.hpp"

const std::string WeaponsHolderComponent::DEFAULT_WEAPON = "DefaultGun";

RTYPE_COMPONENT_IMPL(WeaponsHolderComponent)

void WeaponsHolderComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_defaultWeapon = file.getString("weapon", DEFAULT_WEAPON);
	int tmp = file.getInt("maximum", 4);
	_max = (tmp < 0 ? 4 : tmp);
}

void WeaponsHolderComponent::start()
{
	addWeapon(_defaultWeapon);
	release = false;
}

void WeaponsHolderComponent::update()
{
	auto controller = gameObject().getComponent<APlayerControllable>();
	if (controller)
	{
		auto inputs = controller->getInputs();
		if (inputs && _weapons.size() > 1 && _weapons.back().force)
		{
			if (inputs->isPressed(IPlayerInputs::RELEASE))
			{
				if (!release)
				{
					release = true;
					_weapons.back().force->release();
					if (_weapons.back().weapon)
						_weapons.back().weapon->destroy();
					_weapons.pop_back();
				}
			}
			else
				release = false;
		}
		else
			release = false;
	}
}

void WeaponsHolderComponent::stop()
{
	if (!gameObject().isLocal())
		return ;

	for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
	{
		if (it->weapon)
			it->weapon->destroy();
	}
	_weapons.clear();
}

void WeaponsHolderComponent::addWeapon(const std::string& weapon, AForce* force)
{
	if (!gameObject().isLocal())
		return ;

	if (_weapons.size() < _max)
	{
		rtype::ecs::GameObject* g = NULL;
		bool found = false;
		for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
		{
			if (weapon == it->weaponName)
			{
				found = true;
				break;
			}
		}
		if (!found)
			g = gameEngine().createGameObject(weapon);

		forces f;
		f.force = force;
		f.weaponName = weapon;
		f.weapon = g;
		_weapons.push_back(f);

		if (g)
		{
			auto gt = g->getComponent<ITransform>();

			if (gt)
				gt->setParent(gameObject());

			auto controller = gameObject().getComponent<APlayerControllable>();
			auto controllable = g->getComponent<APlayerControllable>();
			if (controller && controllable)
			{
				controllable->setInputs(controller->getInputs());
				controllable->setPlayer(controller->getPlayer());
			}
		}
	}
}

void WeaponsHolderComponent::upgrade()
{
	for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
	{
		if (it->weapon)
		{
			auto weapon = it->weapon->getComponent<IWeapons>();
			if (weapon)
			{
				weapon->upgrade();
			}
		}
	}
}

void WeaponsHolderComponent::addSpeed(float speed)
{
	for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
	{
		if (it->weapon)
		{
			auto weapon = it->weapon->getComponent<IWeapons>();
			if (weapon)
			{
				weapon->addSpeed(speed);
			}
		}
	}
}

void WeaponsHolderComponent::addDamage(int8_t damage)
{
	for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
	{
		if (it->weapon)
		{
			auto weapon = it->weapon->getComponent<IWeapons>();
			if (weapon)
			{
				weapon->addDamage(damage);
			}
		}
	}
}

bool WeaponsHolderComponent::hasSpace() const
{
	return (_weapons.size() < _max);
}
