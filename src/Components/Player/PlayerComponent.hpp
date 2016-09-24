#ifndef PLAYERCOMPONENT_HPP_
#define PLAYERCOMPONENT_HPP_

#include <memory>
#include <functional>

#include "RType/ECS/AComponent.hpp"
#include "Components/PlayerInputs/IPlayerInputs.hpp"
#include "IPlayerComponent.hpp"

RTYPE_PLUGIN
class PlayerComponent : public rtype::ecs::AComponent, public IPlayerComponent
{
	RTYPE_COMPONENT

private:
	std::string _shipName;
	std::string _lifeTexture;
	rtype::ecs::Vector2u _lifeTextureSize;

	rtype::ecs::GameObject* _ship;
	std::weak_ptr<IPlayerInputs> _inputs;
	int8_t _lives;
	int8_t _damage;

	std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>> _onShipDestroy;

public:
	virtual ~PlayerComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void stop();
	virtual void onGUI();
	virtual void serialize(rtype::system::BinaryWriter& writer);
	virtual void unserialize(rtype::system::BinaryReader& reader);

	virtual void addLife();
	virtual void setDamage(int8_t);
	int8_t getDamage();
	virtual void addSpeed(float);
	virtual void setLives(int8_t);

private:
	void spawnShip();
	void onShipDestroy(rtype::ecs::GameObject&);
};

#endif // !PLAYERCOMPONENT_HPP_
