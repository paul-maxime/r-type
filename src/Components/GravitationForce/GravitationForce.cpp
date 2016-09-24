#include <iostream>
#include "RType/System/Random.hpp"
#include "Components/Weapons/WeaponsHolder/IWeaponsHolder.hpp"
#include "GravitationForce.hpp"
#include "RType/ECS/GameObject.hpp"

RTYPE_COMPONENT_IMPL(GravitationForce)

GravitationForce::GravitationForce()
{
}

GravitationForce::~GravitationForce()
{
}

void GravitationForce::loadFile(const rtype::ecs::file::Value& file)
{
	if (file.hasField("weapons"))
	{
		for (unsigned int i = 0; i < file["weapons"].size(); ++i)
		{
			_weapons.push_back(file["weapons"][i].asString());
		}
	}
}

void GravitationForce::start()
{
	std::shared_ptr<ITransform> transform = gameObject().getComponent<ITransform>();

	_y = transform->getAbsolutePosition().y;
	if (!_weapons.size())
		_weapons.push_back("DefaultGun");
	_weapon = _weapons[rtype::system::random::next(_weapons.size())];
	_cooldown = 2.f;
}

void GravitationForce::update()
{
	if (!gameObject().isLocal()) return;

	_rot += 1.f * gameEngine().getElapsedTime();
	_cooldown += gameEngine().getElapsedTime();

	if (!_taken)
	{
		std::shared_ptr<ITransform> transform = gameObject().getComponent<ITransform>();
		rtype::ecs::Vector3f pos;

		pos = transform->getPosition();
		pos.x -= 100 * gameEngine().getElapsedTime();
		pos.y = sin(_rot) * 120 + _y;
		transform->setPosition(pos);
	}
	else
	{
		std::shared_ptr<ITransform> transform = gameObject().getComponent<ITransform>();
		rtype::ecs::Vector3f pos = transform->getPosition();

		if (transform->hasParent())
		{
			pos.x = 6 + 80 * cos(_rot);
			pos.y = 5 + 80 * sin(_rot);
			transform->setPosition(pos);
		}
		else
			_taken = false;

		if (!_taken)
		{
			std::shared_ptr<ITransform> transform = gameObject().getComponent<ITransform>();
			rtype::ecs::Vector3f pos = transform->getPosition();

			_y = pos.y;
		}
	}
}

void GravitationForce::onCollision(rtype::ecs::GameObject &collision)
{
	if (!_taken && _cooldown > 1)
	{
		std::shared_ptr<IPlayerShip> ship = collision.getComponent<IPlayerShip>();
		auto weaponsHolder = collision.getComponent<IWeaponsHolder>();

		if (ship && weaponsHolder && weaponsHolder->hasSpace())
		{
			std::shared_ptr<ITransform> thisTransform = gameObject().getComponent<ITransform>();
			if (thisTransform)
			{
				std::list<std::shared_ptr<AForce> > forces;

				weaponsHolder->addWeapon(_weapon, this);
				for (auto object : gameEngine().gameObjects())
				{
					std::shared_ptr<AForce> force;

					if ((force = object->getComponent<AForce>()))
					{
						std::shared_ptr<ITransform> forceTransform = object->getComponent<ITransform>();
						if (forceTransform->hasParent() && forceTransform->parentGameObject().instanceId() == collision.instanceId())
							forces.push_back(force);
					}
				}

				int nbr = forces.size();
				if (nbr >= 1)
				{
					float rot = 180.0f / static_cast<float>(nbr);
					int count = 0;

					for (auto force : forces)
					{
						++count;
						force->setRotation(count * rot);
					}
				}
				setRotation(0);
				thisTransform->setParent(collision);
				_taken = true;
			}
		}
	}
}

size_t GravitationForce::getInstanceId()
{
	return (gameObject().instanceId());
}

void GravitationForce::release()
{
	std::shared_ptr<ITransform> thisTransform = gameObject().getComponent<ITransform>();
	if (thisTransform)
	{
		_y = thisTransform->getAbsolutePosition().y;
		if (thisTransform->hasParent())
		{
			auto pTransform = thisTransform->parent();
			if (pTransform)
				thisTransform->setPosition(pTransform->getPosition());
		}
		thisTransform->unsetParent();
		_taken = false;
		_cooldown = 0;
	}
}
