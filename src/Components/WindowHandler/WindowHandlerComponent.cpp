#include "RType/ECS/GameEngine.hpp"
#include "WindowHandlerComponent.hpp"

RTYPE_COMPONENT_IMPL(WindowHandlerComponent)

void WindowHandlerComponent::start()
{
	_escapeTime = 0.0f;
}

void WindowHandlerComponent::update()
{
	if (!gameEngine().hasGraphics()) return;

	gameEngine().getGraphics().updateEvents();
	if (gameEngine().getGraphics().isClosing())
	{
		gameEngine().getGraphics().close();
		gameEngine().stopEngine();
	}

	if (gameEngine().getInputs().keyPressed(rtype::ecs::IInput::Escape)
		|| gameEngine().getInputs().getJoystickButton(rtype::ecs::IInput::Start))
		_escapeTime += gameEngine().getElapsedTime();
	else
		_escapeTime = 0.0f;

	if (_escapeTime > 1.0f)
	{
		gameEngine().loadScene("MenuScene");
		gameEngine().getNetwork().disconnect();
	}
}
