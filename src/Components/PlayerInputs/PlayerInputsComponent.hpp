#ifndef PLAYERINPUTSCOMPONENT_HPP_
#define PLAYERINPUTSCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "RType/System/BinaryReader.hpp"
#include "RType/System/BinaryWriter.hpp"
#include "IPlayerInputs.hpp"

RTYPE_PLUGIN
class PlayerInputsComponent : public rtype::ecs::AComponent, public IPlayerInputs
{
	RTYPE_COMPONENT

public:
	PlayerInputsComponent();
	virtual ~PlayerInputsComponent() {}

	virtual void update();

	virtual void serialize(rtype::system::BinaryWriter& writer);
	virtual void unserialize(rtype::system::BinaryReader& reader);

	virtual bool isPressed(Key key) const;

private:
	bool _enabledKeys[END_KEY];
};

#endif // PLAYERINPUTSCOMPONENT_HPP_
