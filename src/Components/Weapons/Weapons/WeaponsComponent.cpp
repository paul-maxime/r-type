#include <iostream>
#include "RType/ECS/GameEngine.hpp"
#include "RType/ECS/GameObject.hpp"
#include "Components/Behavior/EntitySeeker.hpp"
#include "Components/ShootableEnemy/IShootableEnemy.hpp"
#include "Components/Animations/IAnimations.hpp"
#include "WeaponsComponent.hpp"

const std::unordered_map< std::string, std::string > WeaponsComponent::UPGRADES =
{
	{"gun", "doubleGun"},
	{"doubleGun", "tripleGun"}
};

const std::unordered_map< std::string,
						  std::function<void (WeaponsComponent&,
							  const IPlayerInputs&)> > WeaponsComponent::WEAPONS =
	{
		{ "gun", std::bind(&WeaponsComponent::gun, std::placeholders::_1, std::placeholders::_2) },
		{ "doubleGun", std::bind(&WeaponsComponent::doubleGun, std::placeholders::_1, std::placeholders::_2) },
		{ "tripleGun", std::bind(&WeaponsComponent::tripleGun, std::placeholders::_1, std::placeholders::_2) },
		{ "sideGuns", std::bind(&WeaponsComponent::sideGuns, std::placeholders::_1, std::placeholders::_2) }
	};


RTYPE_COMPONENT_IMPL(WeaponsComponent)

void WeaponsComponent::loadFile(const rtype::ecs::file::Value& file)
{
	if (file.hasField("offset"))
	{
		auto offset = file["offset"];
		if (offset.size() >= 1)
			_offset.x = offset[0].asFloat();
		if (offset.size() >= 2)
			_offset.y = offset[1].asFloat();
		if (offset.size() >= 3)
			_offset.z = offset[2].asFloat();
	}
	_weapon = file.getString("weapon");
	_ammo = file.getString("ammo");
	_cooldown = file.getFloat("cooldown", 0.5f);
	_angle = fmodf(std::abs(file.getFloat("angle", 0.0f)), 360);
	_bulletSpeed = file.getFloat("bullet_speed", 500.0f);
	_damage = file.getInt("damage");
	_guided = file.getBool("guided", false);
	_upgrade = file.getBool("upgrade", true);
}

void WeaponsComponent::start()
{
	_timer = _cooldown;
	_atkPressed = false;
	if (WEAPONS.find(_weapon) == WEAPONS.end())
		_weapon = WEAPONS.begin()->first;

	auto transform = gameObject().getComponent<ITransform>();
	if (transform)
	{
		transform->setPosition(_offset);
	}
}

void WeaponsComponent::update()
{
	if (!gameObject().isLocal()) return;

	_timer += gameEngine().getElapsedTime();

	auto transform = gameObject().getComponent<ITransform>();

	if (transform && transform->hasParent())
	{
		auto inputs = getInputs();
		if (inputs)
			WEAPONS.at(_weapon)(*this, *inputs);
	}
}

void WeaponsComponent::upgrade()
{
	if (_upgrade && UPGRADES.find(_weapon) != UPGRADES.end() &&
		WEAPONS.find(UPGRADES.at(_weapon)) != WEAPONS.end())
	{
		_weapon = UPGRADES.at(_weapon);
	}
}

void WeaponsComponent::addSpeed(float speed)
{
	_bulletSpeed += speed;
}

void WeaponsComponent::addDamage(int8_t damage)
{
	_damage += damage;
}

void WeaponsComponent::startAtkAnim()
{
	auto t = gameObject().getComponent<ITransform>();

	if (t && t->hasParent())
	{
		auto a = t->parentGameObject().getComponent<IAnimations>();

		if (a && !a->willPlay("stopAttack") && !a->willPlay("attack"))
		{
			a->setAnim("startAttack");
			a->queueAnim("attack");
		}
	}
}

void WeaponsComponent::stopAtkAnim()
{
	auto t = gameObject().getComponent<ITransform>();

	if (t && t->hasParent())
	{
		auto a = t->parentGameObject().getComponent<IAnimations>();

		if (a && !a->willPlay("stopAttack") && !a->willPlay("moving"))
		{
			a->setAnim("stopAttack");
			a->queueAnim("moving");
		}
	}
}

void WeaponsComponent::gun(const IPlayerInputs& inputs)
{
	if (inputs.isPressed(IPlayerInputs::ATTACK))
	{
		if (!_atkPressed)
		{
			_atkPressed = true;
			startAtkAnim();
		}

		if (_timer >= _cooldown)
		{
			_timer = 0;
			if (_guided)
			{
				float angle;
				if (EntitySeeker::seekAngle<IShootableEnemy>(gameObject(), gameEngine(), angle))
					_angle = angle;
				else
					_angle = 0;
			}
			createBullet(gameEngine(), gameObject(), _ammo, _bulletSpeed, _angle, _damage + getPlayer()->getDamage());
		}
	}
	else if (_atkPressed)
	{
		_atkPressed = false;
		stopAtkAnim();
	}
}

void WeaponsComponent::doubleGun(const IPlayerInputs& inputs)
{
	if (inputs.isPressed(IPlayerInputs::ATTACK))
	{
		if (!_atkPressed)
		{
			_atkPressed = true;
			startAtkAnim();
		}

		if (_timer >= _cooldown)
		{
			_timer = 0;
			rtype::ecs::Vector2f offset(0, -18);
			createBullet(gameEngine(), gameObject(), _ammo, _bulletSpeed,
						 _angle, _damage, false, offset);
			offset.y = 18;
			createBullet(gameEngine(), gameObject(), _ammo, _bulletSpeed,
						 _angle, _damage, false, offset);
		}
	}
	else if (_atkPressed)
	{
		_atkPressed = false;
		stopAtkAnim();
	}
}

void WeaponsComponent::tripleGun(const IPlayerInputs& inputs)
{
	if (inputs.isPressed(IPlayerInputs::ATTACK))
	{
		if (!_atkPressed)
		{
			_atkPressed = true;
			startAtkAnim();
		}

		if (_timer >= _cooldown)
		{
			_timer = 0;

			float angle = _angle - 20;
			for (unsigned int i = 0; i < 3; ++i)
			{
				createBullet(gameEngine(), gameObject(), _ammo, _bulletSpeed,
							 angle, _damage + getPlayer()->getDamage());
				angle += 20;
			}
		}
	}
	else if (_atkPressed)
	{
		_atkPressed = false;
		stopAtkAnim();
	}
}

void WeaponsComponent::sideGuns(const IPlayerInputs& inputs)
{
	if (inputs.isPressed(IPlayerInputs::ATTACK))
	{
		if (_timer >= _cooldown)
		{
			_timer = 0;

			rtype::ecs::Vector2f offset(0, -35);
			createBullet(gameEngine(), gameObject(), _ammo, _bulletSpeed,
						 _angle, _damage, true, offset);
			offset.y = 35;
			createBullet(gameEngine(), gameObject(), _ammo, _bulletSpeed,
						 - _angle, _damage, true, offset);
		}
	}
}
