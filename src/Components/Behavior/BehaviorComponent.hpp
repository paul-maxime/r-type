#ifndef BEHAVIOR_COMPONENT_HPP_
#define BEHAVIOR_COMPONENT_HPP_

#include "IBehavior.hpp"
#include "RType/ECS/AComponent.hpp"
#include "RType/ECS/GameEngine.hpp"

RTYPE_PLUGIN
class BehaviorComponent : public rtype::ecs::AComponent, public IBehavior
{
	RTYPE_COMPONENT

public:
	BehaviorComponent();
	virtual ~BehaviorComponent() {}

	virtual void start();
	virtual void update();
	virtual void loadFile(const rtype::ecs::file::Value&);

	virtual void setTotalFollowSpeed(float);
	virtual void setSpeed(const rtype::ecs::Vector2f&);
	virtual void setSpeedX(float x);
	virtual void setSpeedY(float y);
	virtual rtype::ecs::Vector2f const & getSpeed() const;
	virtual void setRotationSpeed(float speed);
	virtual float getRotationSpeed() const;

private:
	void updateSpeed(const rtype::ecs::Vector3f& pos);
	rtype::ecs::Vector2f applyWait();
	void followPlayer(rtype::ecs::Vector2f& speed);
	void followEnemy(rtype::ecs::Vector2f& speed);

private:
	std::vector< float > _xSpeeds;
	std::vector< float > _ySpeeds;
	rtype::ecs::Vector2u _idx;
	rtype::ecs::Vector2f _deltaTime;
	rtype::ecs::Vector2f _counter;
	bool _follow;
	bool _followEnemy;
	bool _followRotation;
	float _totalFollowSpeed;
	float _followSpeed;
	float _angle;

	rtype::ecs::Vector2f _speed;
	float _rotationSpeed;
	float _timer;
	float _defaultY;
	float _range;
	float _wait;
	float _duration;
};

#endif /* !BEHAVIOR_COMPONENT_HPP_ */
