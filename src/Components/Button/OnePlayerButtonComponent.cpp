#include "RType/ECS/GameEngine.hpp"
#include "Components/Button/OnePlayerButtonComponent.hpp"

RTYPE_COMPONENT_IMPL(OnePlayerButtonComponent)

OnePlayerButtonComponent::OnePlayerButtonComponent()
{
	_timer = 0.0f;
	_launch = false;
}

void	OnePlayerButtonComponent::update()
{
	if (isClicked() || _launch == true)
	{
		_launch = true;
		_timer += gameEngine().getElapsedTime();
		if ((_launch == true) && (_timer > 1.25f))
		{
			gameEngine().loadScene("SinglePlayerScene");
		}
	}
	AbstractButton::update();
}
