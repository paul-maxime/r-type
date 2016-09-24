#include <algorithm>
#include "RType/ECS/GameEngine.hpp"
#include "PlayerInputsComponent.hpp"

RTYPE_COMPONENT_IMPL(PlayerInputsComponent)

PlayerInputsComponent::PlayerInputsComponent()
{
	std::fill(std::begin(_enabledKeys), std::end(_enabledKeys), false);
}

void PlayerInputsComponent::update()
{
	using namespace rtype::ecs;

	if (!gameEngine().hasGraphics()) return;
	if (!gameObject().isLocal() && !gameObject().isOwner()) return;

	if (gameEngine().getGraphics().isFocused())
	{
		auto& inputs = gameEngine().getInputs();
		_enabledKeys[IPlayerInputs::MOVE_UP] = inputs.keyPressed(IInput::Z)
			|| (inputs.getJoystickAxis(IInput::YAxis) < -50.0f);
		_enabledKeys[IPlayerInputs::MOVE_DOWN] = inputs.keyPressed(IInput::S)
			|| (inputs.getJoystickAxis(IInput::YAxis) > 50.0f);
		_enabledKeys[IPlayerInputs::MOVE_LEFT] = inputs.keyPressed(IInput::Q)
			|| (inputs.getJoystickAxis(IInput::XAxis) < -50.0f);
		_enabledKeys[IPlayerInputs::MOVE_RIGHT] = inputs.keyPressed(IInput::D)
			|| (inputs.getJoystickAxis(IInput::XAxis) > 50.0f);
		_enabledKeys[IPlayerInputs::ATTACK] = inputs.keyPressed(IInput::Space)
			|| inputs.getJoystickButton(IInput::BButton);
		_enabledKeys[IPlayerInputs::RELEASE] = inputs.keyPressed(IInput::X)
			|| inputs.getJoystickButton(IInput::XButton);
	}
	else
		std::fill(std::begin(_enabledKeys), std::end(_enabledKeys), false);
}

void PlayerInputsComponent::serialize(rtype::system::BinaryWriter& writer)
{
	uint8_t pack = (_enabledKeys[0] & 1);

	for (unsigned int i = 1; i < static_cast<unsigned int>(END_KEY); ++i)
		pack |= (_enabledKeys[i] & 1) << i;
	writer << pack;
}

void PlayerInputsComponent::unserialize(rtype::system::BinaryReader& reader)
{
	uint8_t pack;
	reader >> pack;

	for (unsigned int i = 0; i < static_cast<unsigned int>(END_KEY); ++i)
		_enabledKeys[i] = (pack >> i & 1) == 1;
}

bool PlayerInputsComponent::isPressed(IPlayerInputs::Key key) const
{
	return _enabledKeys[static_cast<size_t>(key)];
}
