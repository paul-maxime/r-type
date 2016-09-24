#ifndef PLAYERCONTROLLERCOMPONENT_HPP_
#define PLAYERCONTROLLERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/PlayerInputs/APlayerControllable.hpp"

RTYPE_PLUGIN
class PlayerControllerComponent : public rtype::ecs::AComponent, public APlayerControllable
{
	RTYPE_COMPONENT

private:
	float _speed;

public:
	virtual ~PlayerControllerComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void update();
	virtual void addSpeed(float);
};

#endif // !PLAYERCONTROLLERCOMPONENT_HPP_
