#ifndef SHOOTABLEENEMY_HPP_
#define SHOOTABLEENEMY_HPP_

#include "RType/ECS/AComponent.hpp"
#include "RType/ECS/Color.hpp"
#include "Components/ColliderSystem/ICollision.hpp"
#include "IShootableEnemy.hpp"

RTYPE_PLUGIN
class ShootableEnemy : public rtype::ecs::AComponent, public ICollision, public IShootableEnemy
{
	RTYPE_COMPONENT

private:
	int16_t _life;
	int8_t _team;
	int8_t _damage;
	uint32_t _score;
	rtype::ecs::Color _hitColor;
	float _hitDuration;
	bool _manageDestruction;

	float _colorDelay;
	rtype::ecs::Color _defaultColor;

public:
	virtual ~ShootableEnemy() {}

	virtual void loadFile(const rtype::ecs::file::Value& file);
	virtual void start();
	virtual void update();

	virtual void serialize(rtype::system::BinaryWriter&);
	virtual void unserialize(rtype::system::BinaryReader&);

	virtual void onCollision(rtype::ecs::GameObject &);

	virtual int8_t team() const;
	virtual void doDamage(int8_t);

	virtual int16_t life() const;

private:
	void setColor(const rtype::ecs::Color& color, float duration);
	void incrementScore();
};

#endif // SHOOTABLEENEMY_HPP_
