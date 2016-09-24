#include "RType/ECS/GameEngine.hpp"
#include "GlobalPixelShaderComponent.hpp"

RTYPE_COMPONENT_IMPL(GlobalPixelShaderComponent)

GlobalPixelShaderComponent::GlobalPixelShaderComponent()
{
	_shader = "assets/shaders/pixel/pixel";
	_pixel_w = 1;
	_pixel_h = 1;
	_timer = 0;
	_timeAnim = 1.25f;
	_activate = false;
	_speed = 20.0f;
}

void GlobalPixelShaderComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_pixel_w = file.getFloat("pixel_w");
	_pixel_h = file.getFloat("pixel_h");
	if (_pixel_h > 1 || _pixel_w > 1)
	{
		_timer = _timeAnim;
		_activate = true;
	}
	if (file.hasField("activate"))
	{
		_timer = 0.0f;
		_activate = file.getBool("activate");
	}
}

void GlobalPixelShaderComponent::start()
{
	if (!gameEngine().hasGraphics()) return;

	gameEngine().getGraphics().setGlobalShader(_shader);
	gameEngine().getGraphics().setShaderCurrentTexture(_shader, "sceneTex");
	gameEngine().getGraphics().setShaderParameter(_shader, "pixel_w", _pixel_w);
	gameEngine().getGraphics().setShaderParameter(_shader, "pixel_h", _pixel_h);
	gameEngine().getGraphics().setShaderParameter(_shader, "rt_w", 1024);
	gameEngine().getGraphics().setShaderParameter(_shader, "rt_h", 768);
}

void GlobalPixelShaderComponent::update()
{
	if (!gameEngine().hasGraphics()) return;

	if (_activate && _timer < _timeAnim)
	{
		_pixel_w += (gameEngine().getElapsedTime() / _timeAnim) * _speed;
		_pixel_h += (gameEngine().getElapsedTime() / _timeAnim) * _speed;
		_timer += gameEngine().getElapsedTime();
	}
	else if (!_activate && (_timer < _timeAnim ||  _pixel_w > 1.0f || _pixel_h > 1.0f))
	{
		_pixel_w -= (gameEngine().getElapsedTime() / _timeAnim) * _speed;
		_pixel_h -= (gameEngine().getElapsedTime() / _timeAnim) * _speed;
		if (_pixel_w < 1.0f)
			_pixel_w = 1.0f;
		if (_pixel_h < 1.0f)
			_pixel_h = 1.0f;
		_timer += gameEngine().getElapsedTime();
	}
	gameEngine().getGraphics().setGlobalShader(_shader);
	gameEngine().getGraphics().setShaderCurrentTexture(_shader, "sceneTex");
	gameEngine().getGraphics().setShaderParameter(_shader, "pixel_w", _pixel_w);
	gameEngine().getGraphics().setShaderParameter(_shader, "pixel_h", _pixel_h);
	gameEngine().getGraphics().setShaderParameter(_shader, "rt_w", 1024);
	gameEngine().getGraphics().setShaderParameter(_shader, "rt_h", 768);
}

bool	GlobalPixelShaderComponent::isAnim() const
{
	if (_activate)
		return (_timer < _timeAnim);
	else
		return ((_timer < _timeAnim) || _pixel_w > 1.0f || _pixel_h > 1.0f);
}

void	GlobalPixelShaderComponent::activate()
{
	_activate = !_activate;
	_timer = 0;
}

std::string const &GlobalPixelShaderComponent::getName() const
{
	return _shader;
}
