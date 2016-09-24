#include <iostream>
#include <stdexcept>

#include "RType/ECS/GameEngine.hpp"
#include "AbstractButton.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "Components/Transform/ITransform.hpp"

AbstractButton::AbstractButton()
{
	_menuId = 0;
	_linkMenuId = 0;
	_click = false;
}

void AbstractButton::update()
{
	rtype::ecs::Vector2<float> mouse = gameEngine().getInputs().mousePosition();
	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	auto transform = gameObject().getComponent<ITransform>();

	_click = false;
	if (renderer && transform)
	{
		rtype::ecs::IntRect	rectButton = renderer->getRect();
		rtype::ecs::Vector3f pos = transform->getPosition();
		bool mouseMove = gameEngine().getInputs().onMouseMove();

		if ((mouse.x >= pos.x) && (mouse.x <= pos.x + rectButton.width) &&
			(mouse.y >= pos.y) && (mouse.y <= pos.y + rectButton.height))
		{
			if (gameEngine().getInputs().getClick(rtype::ecs::IInput::LeftClick))
				_click = true;
			if (mouseMove)
				selected();
		}
		else if (mouseMove)
			deselected();
	}
	else
		throw std::runtime_error("Error : " + gameObject().name() +
			" is a button. He needs a sprite renderer and a transform");
}

void AbstractButton::selected()
{
	auto transform = gameObject().getComponent<ITransform>();
	rtype::ecs::Vector2f		size(1.1f, 1.1f);

	transform->setSize(size);
}

void AbstractButton::deselected()
{
	auto transform = gameObject().getComponent<ITransform>();
	rtype::ecs::Vector2f		size(1.0f, 1.0f);

	transform->setSize(size);
}

bool AbstractButton::isClicked() const
{
	return _click;
}

void AbstractButton::setClicked(bool click)
{
	_click = click;
}

void AbstractButton::setMenuId(int id)
{
	_menuId = id;
}

void AbstractButton::setLinkMenuId(int id)
{
	_linkMenuId = id;
}

int AbstractButton::getMenuId() const
{
	return _menuId;
}

int AbstractButton::getLinkMenuId() const
{
	return _linkMenuId;
}
