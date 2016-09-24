#include <iostream>
#include "Components/Behavior/EntitySeeker.hpp"
#include "Components/PlayerShip/IPlayerShip.hpp"
#include "Components/Behavior/IBehavior.hpp"
#include "Components/Animations/IAnimations.hpp"
#include "Components/ShootableEnemy/IShootableEnemy.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "Components/ColliderSystem/ICollider.hpp"
#include "Components/AudioSource/IAudioSource.hpp"
#include "RType/System/Random.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "QueenFlyComponent.hpp"

const std::unordered_map< int,
						  std::function<void (QueenFlyComponent&)> > QueenFlyComponent::PATTERNS =
{
	{ QueenFlyComponent::SPAWN, std::bind(&QueenFlyComponent::spawn, std::placeholders::_1) },
	{ QueenFlyComponent::SALVE, std::bind(&QueenFlyComponent::salve, std::placeholders::_1) },
	{ QueenFlyComponent::WIND, std::bind(&QueenFlyComponent::wind, std::placeholders::_1) },
	{ QueenFlyComponent::RUSH, std::bind(&QueenFlyComponent::rush, std::placeholders::_1) },
	{ QueenFlyComponent::COME_BACK, std::bind(&QueenFlyComponent::comeBack, std::placeholders::_1) },
	{ QueenFlyComponent::DEATH, std::bind(&QueenFlyComponent::death, std::placeholders::_1) }
};

RTYPE_COMPONENT_IMPL(QueenFlyComponent)

void QueenFlyComponent::loadFile(const rtype::ecs::file::Value& file)
{
	if (file.hasField("offset"))
	{
		auto offset = file["offset"];
		if (offset.size() >= 1)
			_offset.x = offset[0].asFloat();
		if (offset.size() >= 2)
			_offset.y = offset[1].asFloat();
	}
	_entrySpeed = file.getFloat("entry_speed", 100.f);
	_salveBullet = file.getString("salve_bullet", "QueenBullet");
	_salveSpeed = file.getFloat("salve_speed", 500.f);
	_salveCd = file.getFloat("salve_cd", 0.15f);
	_windBullet = file.getString("wind_bullet", "QueenWind");
	_windSpeed = file.getFloat("wind_speed", 270.f);
	_windCd = file.getFloat("wind_cd", 1.8f);
	_angerBullet = file.getString("anger_bullet", "QueenAnger");
	_angerBulletSpeed = file.getFloat("anger_bullet_speed", 800.f);
	_angerBulletCd = file.getFloat("anger_bullet_cd", 2.f);
	_deathDuration = file.getFloat("death_duration", 3.f);
	_growlFile = file.getString("growl", "sounds/QueenFlyGrowl.wav");
	_growlVolume = file.getFloat("growl_volume", 50.f);
}

void QueenFlyComponent::start()
{
	if (!gameObject().isLocal())
		return ;

	auto t = gameObject().getComponent<ITransform>();
	if (t)
		_initPosition = t->getAbsolutePosition();
	auto s = gameObject().getComponent<IShootableEnemy>();

	_baseLife = s ? s->life() : 0;
	_anger = 0;
	_pattern = SPAWN;
	_timer = 0;
	_scrolling = rtype::ecs::Vector2f(0, 200);
	_init = false;
	_sign = 1;
	_angerTimer = 0;
	_growl = false;
}

void QueenFlyComponent::update()
{
	growl();
	if (!gameObject().isLocal())
		return;

	_timer += gameEngine().getElapsedTime();
	_eventTimer += gameEngine().getElapsedTime();
	_angerTimer += gameEngine().getElapsedTime();

	auto s = gameObject().getComponent<IShootableEnemy>();
	int16_t currentLife = s ? s->life() : 0;

	if (currentLife <= 0)
		changePattern(DEATH);
	if (_pattern != RUSH && _pattern != SPAWN &&
		((static_cast<float>(currentLife) / static_cast<float>(_baseLife) < 0.66f && _anger == 0) ||
		 (static_cast<float>(currentLife) / static_cast<float>(_baseLife) < 0.33f && _anger == 1)))
	{
		changePattern(RUSH);
		_anger++;
	}
	if (_pattern == SALVE || _pattern == WIND)
		angerShoot();
	if (PATTERNS.find(_pattern) != PATTERNS.end())
		PATTERNS.at(_pattern)(*this);
}

void QueenFlyComponent::serialize(rtype::system::BinaryWriter& writer)
{
	writer << _growl;
}

void QueenFlyComponent::unserialize(rtype::system::BinaryReader& reader)
{
	reader >> _growl;
}

void QueenFlyComponent::setSpeed(const rtype::ecs::Vector2f& speed)
{
	auto b = gameObject().getComponent<IBehavior>();
	if (b)
		b->setSpeed(speed);
}

void QueenFlyComponent::changeAnimation(const std::string& animation)
{
	auto a = gameObject().getComponent<IAnimations>();
	if (a && !a->willPlay(animation))
		a->setAnim(animation);
}

void QueenFlyComponent::changePattern(const Pattern& pattern)
{
	if (_pattern != pattern)
	{
		_pattern = pattern;
		_init = false;
		_eventTimer = 0;
		_timer = 0;
	}
}

bool QueenFlyComponent::center(ITransform& t, float speed)
{
	const rtype::ecs::Vector3f& pos = t.getPosition();

	if (pos.y < 230)
		setSpeed(rtype::ecs::Vector2f(0, speed));
	else if (pos.y > 260)
		setSpeed(rtype::ecs::Vector2f(0, -speed));
	else
	{
		setSpeed(rtype::ecs::Vector2f(0, 0));
		return (true);
	}
	return (false);
}

void QueenFlyComponent::angerShoot()
{
	if (_anger < 1)
		return ;
	if (_angerTimer >= _angerBulletCd - _anger * 0.5f)
	{
		float angle;
		if (EntitySeeker::seekAngle<IPlayerShip>(gameObject(), gameEngine(), angle,
												 rtype::ecs::Vector3f(_offset.x, _offset.y, 0), false))
		{
			createBullet(gameEngine(), gameObject(), _angerBullet, _angerBulletSpeed, angle,
						 0, false, _offset);
		}
		_angerTimer = 0;
	}
}

void QueenFlyComponent::growl()
{
	if (_growl)
	{
		auto audio = gameObject().getComponent<IAudioSource>();
		if (audio)
			audio->playSound(_growlFile, _growlVolume);
		_growl = false;
	}
}

void QueenFlyComponent::spawn()
{
	if (!_init)
	{
		setSpeed(rtype::ecs::Vector2f(-_entrySpeed, 0));
		_init = true;
	}
	if (_timer >= 3.f)
	{
		setSpeed(rtype::ecs::Vector2f(0, 0));
		changePattern(SALVE);
	}
}

void QueenFlyComponent::salve()
{
	if (!_init)
	{
		changeAnimation("attack");
		setSpeed(_scrolling);
		_init = true;
		_angle = 180;
		_anglePower = 1;
	}
	auto t = gameObject().getComponent<ITransform>();

	if (!t)
		return ;
	const rtype::ecs::Vector3f& pos = t->getAbsolutePosition();
	if (pos.y < 50)
		setSpeed(_scrolling);
	else if (pos.y > 500)
		setSpeed(rtype::ecs::Vector2f(0, -_scrolling.y));
	if (_timer >= 8.f)
		changePattern(WIND);
	else if (_eventTimer >= _salveCd)
	{
		createBullet(gameEngine(), gameObject(), _salveBullet, _salveSpeed, _angle,
					 0, false, _offset);
		if (_angle >= 240)
			_anglePower = -1;
		else if (_angle <= 120)
			_anglePower = 1;
		_angle += 20 * _anglePower;
		_eventTimer = 0;
	}
}

void QueenFlyComponent::wind()
{
	auto t = gameObject().getComponent<ITransform>();
	if (!t)
		return ;

	if (!_init)
	{
		if (!center(*t, 300))
			return ;
		changeAnimation("spamming");
		_init = true;
	}
	if (_timer >= 12.f)
		changePattern(SALVE);
	else if (_timer < 10.f && _eventTimer >= _windCd)
	{
		rtype::ecs::Vector2f offset(-t->getAbsolutePosition().x + _initPosition.x,
									-t->getAbsolutePosition().y - 10);
		unsigned int hole = rtype::system::random::next(10) + 3;
		for (unsigned int i = 0; i < 16; ++i)
		{
			if (i != hole && i - 1 != hole)
				createBullet(gameEngine(), gameObject(), _windBullet, _windSpeed, 180.f,
							 0, false, offset + rtype::ecs::Vector2f(0.f, i * 50.f));
		}
		_eventTimer = 0;
	}
}

void QueenFlyComponent::rush()
{
	auto t = gameObject().getComponent<ITransform>();
	if (!t)
		return ;

	if (!_init)
	{
		if (!center(*t, 800))
			return ;
		changeAnimation("raging");
		_growl = true;
		_rushing = false;
		_init = true;
	}

	if (_timer >= 1.8)
	{
		if (!_rushing)
		{
			changeAnimation("moving");
			setSpeed(rtype::ecs::Vector2f(-2000, 0));
			_rushing = true;
		}
		if (t->getPosition().x < -200)
			changePattern(COME_BACK);
	}
	else if (_eventTimer >= 0.05f)
	{
		t->setPosition(t->getPosition() + rtype::ecs::Vector3f(5 * _sign, 0, 0));
		_sign *= -1;
		_eventTimer = 0;
	}
}

void QueenFlyComponent::comeBack()
{
	auto t = gameObject().getComponent<ITransform>();
	if (!t)
		return ;

	if (!_init)
	{
		changeAnimation("moving");
		setSpeed(rtype::ecs::Vector2f(500, 0));
		t->setPosition(t->getPosition() + rtype::ecs::Vector3f(0, 0, 10));
		_init = true;
	}
	if (t->getAbsolutePosition().x>= _initPosition.x + 100)
	{
		t->setPosition(_initPosition);
		changePattern(SPAWN);
	}
}

void QueenFlyComponent::death()
{
	auto sr = gameObject().getComponent<ISpriteRenderer>();
	auto t = gameObject().getComponent<ITransform>();
	if (!sr || !t)
	{
		gameObject().destroy();
		return ;
	}

	if (!_init)
	{
		changeAnimation("death");
		sr->setColor(rtype::ecs::Color(255, 80, 80, 80));
		setSpeed(rtype::ecs::Vector2f(-30, 30));
		_init = true;
	}
	t->setRotation(t->getRotation() - 3 * gameEngine().getElapsedTime());
	if (_eventTimer >= 0.3f)
	{
		explosion(*t);
		_eventTimer = 0;
	}
	if (_timer >= _deathDuration)
		gameObject().destroy();
}

void QueenFlyComponent::explosion(ITransform& t)
{
	auto obj = gameEngine().createGameObject("explosions/Medium");
	auto objT = obj->getComponent<ITransform>();
	auto collider = gameObject().getComponent<ICollider>();
	if (!objT || !collider)
		return ;

	const auto& hitboxes = collider->getHitbox();
	if (hitboxes.size() == 0)
		return;
	size_t rand = rtype::system::random::next(hitboxes.size());
	auto it = hitboxes.begin();
	for (size_t i = 0; i < rand && i < hitboxes.size(); i++)
		it++;
	objT->setPosition(t.getPosition() + rtype::ecs::Vector2f((*it).x, (*it).y));
}
