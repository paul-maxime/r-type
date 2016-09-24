#include "RType/ECS/GameEngine.hpp"
#include "RType/ECS/IGraphicsEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "SpriteRendererComponent.hpp"

RTYPE_COMPONENT_IMPL(SpriteRendererComponent)

void SpriteRendererComponent::loadFile(rtype::ecs::file::Value const& file)
{
	_sprite = file.getString("sprite");

	if (file.hasField("color"))
	{
		rtype::ecs::file::Value color = file["color"];
		uint8_t a = color.getInt("a", 255);
		uint8_t r = color.getInt("r", 255);
		uint8_t g = color.getInt("g", 255);
		uint8_t b = color.getInt("b", 255);
		_color = rtype::ecs::Color(a, r, g, b);
	}
	else
		_color = rtype::ecs::Color(255, 255, 255, 255);

	_shader = NULL;
}

void SpriteRendererComponent::start()
{
	if (!gameEngine().hasGraphics()) return;

	auto t = gameObject().getComponent<ITransform>();

	if (t)
		_lerPos = t->getPosition();

	if (!(_rect.x || _rect.y || _rect.height || _rect.width) && !_sprite.empty())
	{
		rtype::ecs::Vector2u textureSize = gameEngine().getGraphics().getSize(_sprite);
		_rect.width = textureSize.x;
		_rect.height = textureSize.y;
	}
}

void SpriteRendererComponent::draw()
{
	auto t = gameObject().getComponent<ITransform>();

	if (t && _sprite != "")
	{
		std::string		shaderName = "";

		if (_shader)
		{
			_shader->updateShader();
			shaderName = _shader->getName();
		}

		rtype::ecs::Vector2f size = t->getSize();
		size = size / (1 + (t->getPosition().z / 5));

		if (!gameObject().isLocal())
		{
			auto & pos = t->getPosition();
			if (pos.distance(_lerPos) > 10)
				_lerPos = pos.lerp(_lerPos, 0.62f);
			else
				_lerPos = pos;
			gameEngine().getGraphics().draw(_sprite, _lerPos + t->getOrigin(),
				_rect, size, _color, t->getRotation(), t->getOrigin(), shaderName);
		}
		else
			gameEngine().getGraphics().draw(_sprite, t->getAbsolutePosition() + t->getOrigin(),
				_rect, size, _color, t->getRotation(), t->getOrigin(), shaderName);
	}
}

void SpriteRendererComponent::setSprite(const std::string& sprite, const rtype::ecs::IntRect& rect)
{
	_sprite = sprite;
	_rect = rect;
}

void SpriteRendererComponent::setShader(IShader *shader)
{
	_shader = shader;
}

const rtype::ecs::Color& SpriteRendererComponent::getColor() const
{
	return _color;
}

void SpriteRendererComponent::setColor(const rtype::ecs::Color& value)
{
	_color = value;
}

rtype::ecs::IntRect		const &SpriteRendererComponent::getRect() const
{
	return _rect;
}

void	SpriteRendererComponent::setRect(rtype::ecs::IntRect const &rect)
{
	_rect = rect;
}
