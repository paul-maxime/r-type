#include <iostream>
#include "Components/FadeOut/IFadeOut.hpp"
#include "Components/PlayerShip/IPlayerShip.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/Animations/IAnimations.hpp"
#include "Components/Behavior/EntitySeeker.hpp"
#include "AttackComponent.hpp"

const std::string AttackComponent::DEFAULT_BULLET_TYPE = "EnemyBullet";
const std::unordered_map< std::string,
						  std::function<void (AttackComponent&,
											  AttackComponent::Weapon&)> > AttackComponent::ATTACKS =
{
	{ "shoot", std::bind(&AttackComponent::shoot, std::placeholders::_1, std::placeholders::_2) },
	{ "laser", std::bind(&AttackComponent::laser, std::placeholders::_1, std::placeholders::_2) }
};

RTYPE_COMPONENT_IMPL(AttackComponent)

void AttackComponent::parseWeapon(const rtype::ecs::file::Value& file)
{
	Weapon wp;

	wp.atkAnim = file.getString("attack_animation", "attacking");
	wp.startAtkAnim = file.getString("start_attack_animation", "startAttacking");
	wp.stopAtkAnim = file.getString("stop_attack_animation", "stopAttacking");
	std::string bullet = file.getString("bullet");
	if (bullet != "")
		wp.bullets.push_back(bullet);
	if (file.hasField("bullets"))
	{
		auto bullets = file["bullets"];
		for (unsigned int i = 0; i < bullets.size(); ++i)
			wp.bullets.push_back(bullets[i].asString());
	}
	if (file.hasField("offset"))
	{
		auto offset = file["offset"];
		if (offset.size() >= 1)
			wp.offset.x = offset[0].asFloat();
		if (offset.size() >= 2)
			wp.offset.y = offset[1].asFloat();
	}
	if (file.hasField("cooldown"))
	{
		if (file["cooldown"].isArray())
		{
			for (unsigned int i = 0; i < file["cooldown"].size(); ++i)
				wp.cooldown.push_back(file["cooldown"][i].asFloat());
		}
		else
			wp.cooldown.push_back(file.getFloat("cooldown", 2.f));
	}
	if (file.hasField("debug"))
		_debug = file["debug"].asBool();
	else
		_debug = false;
	wp.angle = fmodf(std::abs(file.getFloat("angle", 180.0f)), 360);
	wp.guided = file.getBool("guided", false);
	wp.bulletSpeed = file.getFloat("bullet_speed", 500.0f);
	wp.type = file.getString("type");
	wp.quantity = file.getInt("quantity", 1);
	if (wp.quantity <= 0)
		wp.quantity = 1;
	wp.spread = file.getFloat("spread", 0.f);

	_weapons.push_back(wp);
}

void AttackComponent::loadFile(const rtype::ecs::file::Value& file)
{
	if (file.isArray())
	{
		for (unsigned int i = 0; i < file.size(); ++i)
			parseWeapon(file[i]);
	}

	else
		parseWeapon(file);
}

void AttackComponent::start()
{
	_idx = 0;
	for (auto it = _weapons.begin(); it != _weapons.end(); ++it)
	{
		it->timer = 0;
		if (ATTACKS.find(it->type) == ATTACKS.end())
			it->type = ATTACKS.begin()->first;
		if (it->bullets.size() == 0)
			it->bullets.push_back(DEFAULT_BULLET_TYPE);
		it->playedAtk = false;
		it->cdIdx = 0;
		if (it->cooldown.size() == 0)
			it->cooldown.push_back(2.f);
	}
}

void AttackComponent::update()
{
	if (!gameObject().isLocal()) return;

	if (_weapons.size())
	{
		_weapons[_idx].timer += gameEngine().getElapsedTime();

		setupAtkAnim(_weapons[_idx]);
		if (_weapons[_idx].timer >= _weapons[_idx].cooldown[_weapons[_idx].cdIdx])
		{
			_weapons[_idx].timer = 0;
			playAtkAnim(_weapons[_idx]);
			if (_weapons[_idx].guided)
				updateAim(_weapons[_idx]);
			ATTACKS.at(_weapons[_idx].type)(*this, _weapons[_idx]);
			_weapons[_idx].playedAtk = false;
			if (++(_weapons[_idx].cdIdx) >= _weapons[_idx].cooldown.size())
			{
				_weapons[_idx].cdIdx = 0;
				if (++_idx >= _weapons.size())
					_idx = 0;
			}
		}
	}
}

void AttackComponent::updateAim(Weapon& wp)
{
	float angle;
	if (EntitySeeker::seekAngle<IPlayerShip>(gameObject(), gameEngine(), angle,
											 rtype::ecs::Vector3f(wp.offset.x, wp.offset.y, 0), false))
		wp.angle = angle;
}

void AttackComponent::setupAtkAnim(Weapon& wp)
{
	if (!wp.playedAtk && wp.cdIdx == 0)
	{
		auto a = gameObject().getComponent<IAnimations>();

		if (a)
		{
			float time = a->getAnimationDuration(wp.startAtkAnim);
			if (a->hasAnimation(wp.startAtkAnim) && !a->willPlay(wp.startAtkAnim) &&
				time < wp.cooldown[wp.cdIdx] && wp.cooldown[wp.cdIdx] - wp.timer <= time)
			{
				wp.playedAtk = true;
				a->setAnim(wp.startAtkAnim);
				a->queueAnim(wp.atkAnim);
				a->queueAnim(wp.stopAtkAnim);
				a->queueAnim("moving");
			}
		}
	}
}

void AttackComponent::playAtkAnim(Weapon& wp)
{
	if (!wp.playedAtk && wp.cdIdx == 0)
	{
		auto a = gameObject().getComponent<IAnimations>();

		if (a && a->hasAnimation(wp.atkAnim) && !a->willPlay(wp.atkAnim))
		{
			wp.playedAtk = true;
			a->setAnim(wp.atkAnim);
			a->queueAnim(wp.stopAtkAnim);
			a->queueAnim("moving");
		}
	}
}

void AttackComponent::shoot(Weapon& wp)
{
	float inc = (wp.spread < 360 && wp.quantity > 1 && wp.quantity % 2 ?
				 wp.spread / (wp.quantity - 1) : wp.spread / wp.quantity);
	float angle = wp.spread >= 360 ? 0 : wp.angle - inc;

	for (int i = 0; i < wp.quantity; ++i)
	{
		createBullet(gameEngine(), gameObject(), wp.bullets[0], wp.bulletSpeed,
					 angle, 0, false, wp.offset);
		angle += inc;
	}
}

void AttackComponent::laser(Weapon& wp)
{
	auto bullet = gameEngine().createGameObject(wp.bullets[0]);

	if (bullet)
	{
		auto t = bullet->getComponent<ITransform>();
		if (t)
		{
			t->setParent(gameObject());
			t->setPosition(wp.offset);
		}

		auto fade = bullet->getComponent<IFadeOut>();
		if (fade)
		{
			wp.timer -= fade->getDuration();
		}
	}
}

void AttackComponent::draw()
{
	using namespace rtype::ecs;

	if (_debug)
	{
		auto t = gameObject().getComponent<ITransform>();

		if (t)
		{
			for (auto const & e : _weapons)
			{
				gameEngine().getGraphics().draw("sprites/cross.png",
					t->getAbsolutePosition() + e.offset + Vector2f(-6.25, -6.25),
					rtype::ecs::IntRect(),
					Vector2f(0.5f, 0.5f));
			}
		}
	}
}
