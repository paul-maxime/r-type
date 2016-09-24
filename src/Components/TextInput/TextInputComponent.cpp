#include <cctype>

#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/TextRenderer/ITextRenderer.hpp"
#include "TextInputComponent.hpp"

RTYPE_COMPONENT_IMPL(TextInputComponent)

TextInputComponent::TextInputComponent()
{
	_spriteOn = "";
	_spriteOff = "";
	_selected = false;
}

void TextInputComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_spriteOn = file.getString("spriteOn");
	_spriteOff = file.getString("spriteOff");
	_string = file.getString("text");
}

void TextInputComponent::start()
{
	rtype::ecs::Vector2u size = gameEngine().getGraphics().getSize(_spriteOn);
	_rect.height = size.y;
	_rect.width = size.x;

	auto t = gameObject().getComponent<ITransform>();

	if (t)
		_lerPos = t->getPosition();
}

void TextInputComponent::update()
{
		rtype::ecs::Vector2<float> mouse = gameEngine().getInputs().mousePosition();
		auto transform = gameObject().getComponent<ITransform>();

		if (transform)
		{
			rtype::ecs::Vector3f pos = transform->getPosition();
			bool mouseMove = gameEngine().getInputs().onMouseMove();

			if ((mouse.x >= pos.x) && (mouse.x <= pos.x + _rect.width) &&
				(mouse.y >= pos.y) && (mouse.y <= pos.y + _rect.height))
			{
				if (gameEngine().getInputs().getClick(rtype::ecs::IInput::LeftClick))
					_selected = true;
				if (mouseMove)
					selected();
			}
			else if (mouseMove)
			{
				_selected = false;
				deselected();
			}
		}
		else
			throw std::runtime_error("Error : " + gameObject().name() +
				" needs a transform component");
	if (_selected == true)
	{
		std::string str = gameEngine().getInputs().getTypedString();

		for (char c : str)
		{
			if (std::isprint(c))
				_string.push_back(c);
			else if (c == '\b' && !_string.empty())
				_string.pop_back();
		}

		rtype::ecs::IInput::key	key;
		float axis = gameEngine().getInputs().getJoystickAxis(rtype::ecs::IInput::axis::YAxis);

		if (gameEngine().getInputs().onKeyDown(key) || axis > 90.0f || axis < -90.0f)
			if (key == rtype::ecs::IInput::key::Down ||
				key == rtype::ecs::IInput::key::Up ||
				axis > 90.0f || axis < -90.0f)
				_selected = false;
	}
}

void TextInputComponent::selected()
{
	auto transform = gameObject().getComponent<ITransform>();
	rtype::ecs::Vector2f		size(1.1f, 1.1f);

	transform->setSize(size);
}

void TextInputComponent::deselected()
{
	auto transform = gameObject().getComponent<ITransform>();
	rtype::ecs::Vector2f		size(1.0f, 1.0f);

	transform->setSize(size);
}

void TextInputComponent::draw()
{
	auto		transform = gameObject().getComponent<ITransform>();
	if (transform)
	{
		auto	size = transform->getSize();

		if (_selected)
			gameEngine().getGraphics().draw(_spriteOn, _lerPos, _rect, size);
		else
			gameEngine().getGraphics().draw(_spriteOff, _lerPos, _rect, size);

		auto renderer = gameObject().getComponent<ITextRenderer>();

		if (renderer)
			renderer->setText(_string);
	}
	else
		throw std::runtime_error("Error : " + gameObject().name() + " need a Transform component.");
}

void TextInputComponent::setSelected(bool selected)
{
	_selected = selected;
}
