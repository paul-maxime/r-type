#include "RType/ECS/GameEngine.hpp"
#include "WaveShaderComponent.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"

RTYPE_COMPONENT_IMPL(WaveShaderComponent)

WaveShaderComponent::WaveShaderComponent()
{
	_shader = "assets/shaders/wave/wave";
	_wave_phase = 0.0f;
	_activate = true;
}

void WaveShaderComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_wave_amplitudeX = file.getFloat("wave_amplitudeX");
	_wave_amplitudeY = file.getFloat("wave_amplitudeY");
}

void WaveShaderComponent::start()
{
	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	if (renderer)
	{
		renderer->setShader(this);
	}
}

void WaveShaderComponent::update()
{
	if (_activate)
	{
		_wave_phase += gameEngine().getElapsedTime();
		 if (_wave_phase > 600.0f)
			 _wave_phase *= -1.0f;
		_waX = _wave_amplitudeX;
		_waY = _wave_amplitudeY;
	}
	else
	{
		_wave_phase = 0.0f;
		_waX = 0.0f;
		_waY = 0.0f;
	}
}

void WaveShaderComponent::updateShader()
{
	rtype::ecs::IGraphicsEngine	&graphics = gameEngine().getGraphics();

	graphics.setShaderCurrentTexture(_shader, "sceneTex");
	graphics.setShaderParameter(_shader, "wave_phase", _wave_phase);
	graphics.setShaderParameter(_shader, "wave_amplitudeX", _waX);
	graphics.setShaderParameter(_shader, "wave_amplitudeY", _waY);
}

std::string const &WaveShaderComponent::getName() const
{
	return _shader;
}

void	WaveShaderComponent::activate()
{
	_activate = !_activate;
}
