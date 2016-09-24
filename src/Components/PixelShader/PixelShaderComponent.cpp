#include <iostream>

#include "RType/ECS/GameEngine.hpp"
#include "PixelShaderComponent.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"

RTYPE_COMPONENT_IMPL(PixelShaderComponent)

PixelShaderComponent::PixelShaderComponent()
{
	_shader = "assets/shaders/pixel/pixel";
	_pixel_w = 1;
	_pixel_h = 1;
	_timer = 0;
	_timeAnim = 1.25f;
	_activate = false;
	_speed = 20.0f;
}

void PixelShaderComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_pixel_w = file.getFloat("pixel_w");
	_pixel_h = file.getFloat("pixel_h");
	if (_pixel_h > 1 || _pixel_w > 1)
	{
		_timer = _timeAnim;
		_activate = true;
	}
}

void PixelShaderComponent::start()
{
	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	if (renderer)
	{
		renderer->setShader(this);
	}
}

void PixelShaderComponent::update()
{
	auto renderer = gameObject().getComponent<ISpriteRenderer>();

	if (renderer)
		_rect = renderer->getRect();
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
}

void PixelShaderComponent::updateShader()
{
	rtype::ecs::IGraphicsEngine	&graphics = gameEngine().getGraphics();
	rtype::ecs::IntRect rect;

	graphics.setShaderCurrentTexture(_shader, "sceneTex");
	graphics.setShaderParameter(_shader, "rt_w", static_cast<float>(_rect.width));
	graphics.setShaderParameter(_shader, "rt_h", static_cast<float>(_rect.height));
	graphics.setShaderParameter(_shader, "pixel_w", _pixel_w);
	graphics.setShaderParameter(_shader, "pixel_h", _pixel_h);
}

bool PixelShaderComponent::isAnim() const
{
	if (_activate)
		return (_timer < _timeAnim);
	else
		return ((_timer < _timeAnim) || _pixel_w > 1.0f || _pixel_h > 1.0f);
}

std::string const &PixelShaderComponent::getName() const
{
	return _shader;
}

void	PixelShaderComponent::activate()
{
	_activate = !_activate;
	_timer = 0;
}
