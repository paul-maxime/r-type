#ifndef QUEEN_FLY_HPP_
#define QUEEN_FLY_HPP_

#include <string>
#include <functional>
#include <unordered_map>
#include "Components/Weapons/BulletSpawner/BulletSpawner.hpp"
#include "Components/Transform/ITransform.hpp"
#include "RType/ECS/Vector2.hpp"
#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class QueenFlyComponent : public rtype::ecs::AComponent, public BulletSpawner
{
	RTYPE_COMPONENT

public:
	enum Pattern
		{
			SPAWN,
			SALVE,
			WIND,
			RUSH,
			COME_BACK,
			DEATH
		};

private:
	static const std::unordered_map<int, std::function<void (QueenFlyComponent&)>> PATTERNS;

public:
	virtual ~QueenFlyComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void serialize(rtype::system::BinaryWriter&);
	virtual void unserialize(rtype::system::BinaryReader&);

private:
	void setSpeed(const rtype::ecs::Vector2f&);
	void changeAnimation(const std::string&);
	void changePattern(const Pattern&);

	bool center(ITransform&, float);
	void angerShoot();
	void growl();

	void spawn();
	void salve();
	void wind();
	void rush();
	void comeBack();
	void death();

	void explosion(ITransform& t);
private:
	rtype::ecs::Vector3f _initPosition;
	float _init;
	Pattern _pattern;
	int16_t _baseLife;
	float _entrySpeed;
	rtype::ecs::Vector2f _scrolling;
	rtype::ecs::Vector2f _offset;
	unsigned int _anger;
	float _timer;
	float _angle;
	float _anglePower;
	float _eventTimer;
	float _sign;

	std::string _growlFile;
	float _growlVolume;
	bool _growl;

	/* anger */
	std::string _angerBullet;
	float _angerBulletSpeed;
	float _angerBulletCd;
	float _angerTimer;

	/* Salve */
	std::string _salveBullet;
	float _salveCd;
	float _salveSpeed;

	/* Wind */
	std::string _windBullet;
	float _windCd;
	float _windSpeed;

	/* Rush */
	bool _rushing;

	/* Death */
	float _deathDuration;
};

#endif /* !QUEEN_FLY_HPP_ */
