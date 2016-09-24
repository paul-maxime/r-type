#include <iostream>

#include "RType/ECS/GameEngine.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "ShaderComponent.hpp"

RTYPE_COMPONENT_IMPL(ShaderComponent)

ShaderComponent::ShaderComponent()
{
	_shader = "";
	_varText = "";
}

ShaderComponent::~ShaderComponent()
{
}

void ShaderComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_shader = file.getString("shader");
	_varText = file.getString("paramTexture");
	if (file.hasField("param"))
	{
		const rtype::ecs::file::Value param = file["param"];
		for (const std::string& name : param.fieldNames())
		{
			_values[name] = param[name].asFloat();
		}
	}
}

void ShaderComponent::start()
{
	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	if (renderer)
	{
		renderer->setShader(this);
	}
}

std::string const		&ShaderComponent::getName() const
{
	return _shader;
}

void ShaderComponent::updateShader()
{
	if (!_shader.empty() && !_varText.empty())
	{
		rtype::ecs::IGraphicsEngine	&graphics = gameEngine().getGraphics();
		std::unordered_map<std::string, float>::iterator		it = _values.begin();

		graphics.setShaderCurrentTexture(_shader, _varText);
		while (it != _values.end())
		{
			graphics.setShaderParameter(_shader, (*it).first, (*it).second);
			it++;
		}
	}
}

void ShaderComponent::activate()
{
}
