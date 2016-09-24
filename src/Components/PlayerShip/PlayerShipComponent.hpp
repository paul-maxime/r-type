#ifndef PLAYERSHIPCOMPONENT_HPP_
#define PLAYERSHIPCOMPONENT_HPP_

#include <vector>

#include "RType/ECS/AComponent.hpp"
#include "IPlayerShip.hpp"

RTYPE_PLUGIN
class PlayerShipComponent : public rtype::ecs::AComponent, public IPlayerShip
{
	RTYPE_COMPONENT

private:
	std::string _explosion;
	rtype::ecs::Vector3f _explosionDelta;
	uint8_t _spriteID;
	std::vector<std::string> _shipName;

	float _invulnerabilityTime;
	rtype::ecs::Color _originalColor;
	bool _isCurrentPlayer;

public:
	virtual ~PlayerShipComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value& file);
	virtual void start();
	virtual void update();
	virtual void serialize(rtype::system::BinaryWriter&);
	virtual void unserialize(rtype::system::BinaryReader&);

	virtual bool hit();

private:
	void blink();
	void spawnExplosion();
};

#endif // !PLAYERSHIPCOMPONENT_HPP_
