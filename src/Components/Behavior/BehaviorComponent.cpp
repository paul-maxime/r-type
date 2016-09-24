#include <iostream>
#include <cmath>
#include <cctype>
#include "Components/ColliderSystem/ICollider.hpp"
#include "Components/ShootableEnemy/IShootableEnemy.hpp"
#include "Components/PlayerShip/IPlayerShip.hpp"
#include "Components/Transform/ITransform.hpp"
#include "EntitySeeker.hpp"
#include "BehaviorComponent.hpp"

RTYPE_COMPONENT_IMPL(BehaviorComponent)

BehaviorComponent::BehaviorComponent()
{
	_defaultY = 0;
	_timer = 0;
}

void BehaviorComponent::loadFile(const rtype::ecs::file::Value& file)
{
	if (file.hasField("xMovements"))
	{
		auto xm = file["xMovements"];

		for (unsigned int i = 0; i < xm.size(); ++i)
			_xSpeeds.push_back(xm[i].asFloat());
	}
	if (file.hasField("yMovements"))
	{
		auto ym = file["yMovements"];

		for (unsigned int i = 0; i < ym.size(); ++i)
			_ySpeeds.push_back(ym[i].asFloat());
	}
	_deltaTime.x = file.getFloat("deltaTimeX", 1.f);
	_deltaTime.y = file.getFloat("deltaTimeY", 1.f);

	_speed.x = file.getFloat("speedX");
	_speed.y = file.getFloat("speedY");
	_rotationSpeed = file.getFloat("rotationSpeed");

	_range = file.getFloat("range");
	_wait = file.getFloat("wait");
	_duration = file.getFloat("duration");
	_follow = file.getBool("follow", false);
	_followEnemy = file.getBool("follow_enemy", false);
	_followRotation = file.getBool("follow_rotation", false);
	_followSpeed = file.getFloat("follow_speed", 100.f);
	_totalFollowSpeed = file.getFloat("total_follow_speed", 100.f);

	if (_wait < 0)
		_wait = 0;
	if (_duration < 0)
		_duration = 0;
}

void BehaviorComponent::setTotalFollowSpeed(float speed)
{
	_totalFollowSpeed = speed;
}

void BehaviorComponent::setSpeed(const rtype::ecs::Vector2f& speed)
{
	_speed = speed;
}

void BehaviorComponent::setSpeedX(float x)
{
	_speed.x = x;
}

void BehaviorComponent::setSpeedY(float y)
{
	_speed.y = y;
}

rtype::ecs::Vector2f const & BehaviorComponent::getSpeed() const
{
	return _speed;
}

void BehaviorComponent::setRotationSpeed(float speed)
{
	_rotationSpeed = speed;
}

float BehaviorComponent::getRotationSpeed() const
{
	return _rotationSpeed;
}

void BehaviorComponent::start()
{
	auto t = gameObject().getComponent<ITransform>();

	if (t)
		_defaultY = t->getPosition().y;

	if (_xSpeeds.size())
		_speed.x = _xSpeeds[0];
	if (_ySpeeds.size())
		_speed.y = _ySpeeds[0];

	_idx.x = _idx.y = 0;
	_counter.x = _deltaTime.x;
	_counter.y = _deltaTime.y;
	_angle = 0;
}

void BehaviorComponent::update()
{
	if (!gameObject().isLocal()) return;

	auto t = gameObject().getComponent<ITransform>();

	if (t)
	{
		_timer += gameEngine().getElapsedTime();

		updateSpeed(t->getPosition());

		rtype::ecs::Vector2f speed = applyWait();
		if (_follow)
			followPlayer(speed);
		else if (_followEnemy)
			followEnemy(speed);

		t->move(speed.x * gameEngine().getElapsedTime(), speed.y * gameEngine().getElapsedTime());
		if (_rotationSpeed && !_follow && !_followEnemy)
			t->rotate(_rotationSpeed * gameEngine().getElapsedTime());
	}
}

void BehaviorComponent::updateSpeed(const rtype::ecs::Vector3f& pos)
{
	if (_range)
	{
		if (pos.y > _defaultY + _range)
			_speed.y = -std::abs(_speed.y);
		else if (pos.y < _defaultY - _range)
			_speed.y = std::abs(_speed.y);
	}
	if (_xSpeeds.size() && (_counter.x -= gameEngine().getElapsedTime()) <= 0)
	{
		_counter.x = _deltaTime.x;
		_idx.x = (_idx.x + 1) % _xSpeeds.size();
		_speed.x = _xSpeeds[_idx.x];
	}
	if (_ySpeeds.size() && (_counter.y -= gameEngine().getElapsedTime()) <= 0)
	{
		_counter.y = _deltaTime.y;
		_idx.y = (_idx.y + 1) % _ySpeeds.size();
		_speed.y = _ySpeeds[_idx.y];
	}
}

rtype::ecs::Vector2f BehaviorComponent::applyWait()
{
	rtype::ecs::Vector2f speed(0, 0);
	if (_wait > 0)
	{
		if (_timer < _wait)
		{
			speed.x = (1 - _timer / _wait) * _speed.x;
			speed.y = (1 - _timer / _wait) * _speed.y;
		}
		else if (_timer > _wait + _duration)
		{
			speed.x = ((_timer - _duration) / _wait - 1) * _speed.x;
			speed.y = ((_timer - _duration) / _wait - 1) * _speed.y;
		}
	}
	else
		speed = _speed;
	return (speed);
}

void BehaviorComponent::followPlayer(rtype::ecs::Vector2f& speed)
{
	rtype::ecs::Vector3f pos;

	if (!EntitySeeker::seekPosition<IPlayerShip>(gameObject(), gameEngine(), pos))
		return ;

	auto self = gameObject().getComponent<ITransform>();
	rtype::ecs::Vector3f mpos = self->getAbsolutePosition();

	auto mCollider = gameObject().getComponent<ICollider>();
	if (mCollider)
	{
		auto mHitboxes = mCollider->getHitbox();
		if (mHitboxes.size())
			mpos += rtype::ecs::Vector3f(mHitboxes.front().x + mHitboxes.front().width / 2,
										 mHitboxes.front().y + mHitboxes.front().height / 2, 0);
	}

	float diff = pos.y > mpos.y ? pos.y - mpos.y : mpos.y - pos.y;
	if (std::abs(diff) > 2)
		speed.y = pos.y < mpos.y ? -_followSpeed : _followSpeed;
	else
		speed.y = 0;
	_speed.y = speed.y;
}

void BehaviorComponent::followEnemy(rtype::ecs::Vector2f& speed)
{
	float angle;
	if (!EntitySeeker::seekAngle<IShootableEnemy>(gameObject(), gameEngine(), angle))
	{
		angle = _angle;
	}

	auto t = gameObject().getComponent<ITransform>();
	if (_followRotation)
	{
		float curAngle = fmodf(360 - t->getRotation(), 360);
		if (curAngle < 0)
			curAngle = 360 + curAngle;

		float dist1 = (angle > curAngle ? angle - curAngle : 360 - curAngle + angle);
		float dist2 = (angle > curAngle ? 360 - angle + curAngle : curAngle - angle);
		float inc = _rotationSpeed * gameEngine().getElapsedTime();

		if (dist1 < dist2)
			inc = (inc < dist1 ? inc : dist1);
		else
			inc = -(inc < dist2 ? inc : dist2);

		angle = curAngle + inc;
		angle = fmodf(angle, 360);
		if (angle < 0)
			angle = 360 + angle;
		t->setRotation(360 - angle);
	}
	
	float ang = ((angle <= 90 && angle >= 0) || (angle > 180 && angle <= 270) ?
				 fmodf(angle, 91) : (angle <= 180 ? 180 - angle : 360 - angle));
	int dirX = (angle >= 90 && angle <= 270 ? -1 : 1), dirY = (angle >= 0 && angle <= 180 ? -1 : 1);
	float vx = std::cos(ang * 3.14159265f / 180.f), vy = std::sin(ang * 3.14159265f / 180.f);

	float norme = std::sqrt(vx * vx + vy * vy);
	speed.x = vx / norme * _totalFollowSpeed * dirX;
	speed.y = vy / norme * _totalFollowSpeed * dirY;
	_angle = angle;
}
