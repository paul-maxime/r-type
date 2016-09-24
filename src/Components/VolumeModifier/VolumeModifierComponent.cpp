#include <iostream>

#include "RType/ECS/GameEngine.hpp"
#include "VolumeModifierComponent.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "Components/Transform/ITransform.hpp"

RTYPE_COMPONENT_IMPL(VolumeModifierComponent)

void VolumeModifierComponent::start()
{
	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	auto transform = gameObject().getComponent<ITransform>();

	if (renderer && transform)
	{
		_rect = renderer->getRect();
		_pos = transform->getPosition();
	}
	else
		throw std::runtime_error("Error : " + gameObject().name() +
			" needs a sprite renderer and a transform");
	_timeAxis = 0.0f;
}

void VolumeModifierComponent::update()
{
	rtype::ecs::IInput::key		key;
	float						axis = gameEngine().getInputs().getJoystickAxis(rtype::ecs::IInput::axis::XAxis);

	if (gameEngine().getInputs().getClick(rtype::ecs::IInput::LeftClick))
	{
		rtype::ecs::Vector2<float> mouse = gameEngine().getInputs().mousePosition();

		if ((mouse.x >= _pos.x) && (mouse.x <= _pos.x + _rect.width) &&
			(mouse.y >= _pos.y) && (mouse.y <= _pos.y + _rect.height))
		{
			float vol = ((mouse.x - _pos.x) * 100.0f) / _rect.width;

			setVolume(vol);
		}
	}
	if (axis < 70.0f && axis > -70.0f)
		_timeAxis = 0.0f;
	if (gameEngine().getInputs().onKeyDown(key) ||
		((axis > 90.0f || axis < -90.0f) && _timeAxis <= 0.0f))
	{
		_timeAxis = 0.10f;
		if (key == rtype::ecs::IInput::key::Left || axis < -90.0f)
		{
			rtype::ecs::Vector2f	size = gameObject().getComponent<ITransform>()->getSize();

			if (size.x > 1.0f && size.y > 1.0f)
			{
				float vol = gameEngine().getAudio().getVolume();

				if ((vol -= 5.0f) < 0.0f)
					vol = 0.0f;

				setVolume(vol);
			}
		}
		else if (key == rtype::ecs::IInput::key::Right || axis > 90.0f)
		{
			rtype::ecs::Vector2f	size = gameObject().getComponent<ITransform>()->getSize();

			if (size.x > 1.0f && size.y > 1.0f)
			{
				float vol = gameEngine().getAudio().getVolume();

				if ((vol += 5.0f) > 100.0f)
					vol = 100.0f;

				setVolume(vol);
			}
		}
	}
	_timeAxis -= gameEngine().getElapsedTime();
}

void VolumeModifierComponent::setVolume(float vol)
{
	rtype::ecs::IntRect	newRect = _rect;
	gameEngine().getAudio().setVolume(vol);
	newRect.width = static_cast<int>(static_cast<float>(newRect.width) * (vol / 100.0f));
	gameObject().getComponent<ISpriteRenderer>()->setRect(newRect);
}
