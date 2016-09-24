#include "RType/ECS/GameEngine.hpp"
#include "GlobalBlinkShaderComponent.hpp"

RTYPE_COMPONENT_IMPL(GlobalBlinkShaderComponent)

GlobalBlinkShaderComponent::GlobalBlinkShaderComponent()
{
	_shader = "assets/shaders/blink/blink";
	_blink_alpha = 1.0f;

	_timeAnim = 0.0001f;
	_timer = 0;
	_activate = false;
}

void GlobalBlinkShaderComponent::loadFile(const rtype::ecs::file::Value&)
{

}

void GlobalBlinkShaderComponent::start()
{
}

void GlobalBlinkShaderComponent::update()
{
	if (_activate && _timer < _timeAnim)
	{
		gameEngine().getGraphics().setGlobalShader(_shader);
		gameEngine().getGraphics().setShaderParameter(_shader, "blink_alpha", _blink_alpha);
		_timer += gameEngine().getElapsedTime();
	}
	else
	{
		gameEngine().getGraphics().setGlobalShader("");
		_activate = false;
		_timer = 0.0f;
	}
}

bool GlobalBlinkShaderComponent::isAnim() const
{
	return _activate;
}

void GlobalBlinkShaderComponent::activate()
{
	_activate = true;
}

std::string const &GlobalBlinkShaderComponent::getName() const
{
	return _shader;
}
