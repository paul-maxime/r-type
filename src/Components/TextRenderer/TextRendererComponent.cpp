#include <stdexcept>

#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "TextRendererComponent.hpp"

RTYPE_COMPONENT_IMPL(TextRendererComponent)

void TextRendererComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_font = file.getString("font");
	_text = file.getString("text");
	_size = file.getInt("size");
	if (file.hasField("color"))
	{
		rtype::ecs::file::Value color = file["color"];
		uint8_t a = color.getInt("a", 255);
		uint8_t r = color.getInt("r");
		uint8_t g = color.getInt("g");
		uint8_t b = color.getInt("b");
		_color = rtype::ecs::Color(a, r, g, b);
	}
	_shadow = file.getBool("shadow");
	if (file.hasField("delta"))
	{
		rtype::ecs::file::Value delta = file["delta"];
		_delta.x = delta[0].asFloat();
		_delta.y = delta[1].asFloat();
	}
	_subline = file.getBool("subline");
}

void TextRendererComponent::start()
{
	if (!gameObject().getComponent<ITransform>())
		throw std::runtime_error("TextRenderer without a Transform");

	setText(_text);
}

void TextRendererComponent::draw()
{
	if (!gameEngine().hasGraphics()) return;

	if (_subline)
	{
		draw(_text, _size);
		draw(_subtext, _size / 2);
	}
	else
	{
		draw(_text, _size);
	}
}

void TextRendererComponent::setText(const std::string& text)
{
	_text = text;

	std::string::size_type pos;
	if (_subline && (pos = _text.find('\n')) != std::string::npos)
	{
		std::string text = _text.substr(0, pos);
		_subtext = "\n" + _text.substr(pos);
		_text = text;
	}
}

const std::string& TextRendererComponent::getText() const
{
	return _text;
}

void TextRendererComponent::draw(const std::string& text, uint32_t size)
{
	auto transform = gameObject().getComponent<ITransform>();
	rtype::ecs::Vector3f pos = transform->getPosition() + _delta;
	if (_shadow)
	{
		rtype::ecs::Vector3f shadowPos = pos + rtype::ecs::Vector3f(3.0f, 3.0f, 0.0f);
		gameEngine().getGraphics().drawText(_font, text, size,
			rtype::ecs::Vector2f(shadowPos.x, shadowPos.y),
			rtype::ecs::Color(255, 0, 0, 0));
	}

	gameEngine().getGraphics().drawText(_font, text, size,
		rtype::ecs::Vector2f(pos.x, pos.y), _color);
}
