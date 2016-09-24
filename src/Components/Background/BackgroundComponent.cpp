#include <utility>

#include "RType/ECS/GameEngine.hpp"
#include "BackgroundComponent.hpp"

RTYPE_COMPONENT_IMPL(BackgroundComponent)

void BackgroundComponent::loadFile(const rtype::ecs::file::Value& file)
{
	for (size_t i = 0; i < file.size(); ++i)
	{
		rtype::ecs::file::Value elem = file[i];
		Background bg;
		bg.sprite = elem.getString("sprite");
		bg.speed = elem.getFloat("speed");
		bg.pos = 0.0f;
		bg.size = 0.0f;

		if (elem.hasField("color"))
		{
			rtype::ecs::file::Value color = elem["color"];
			uint8_t a = color.getInt("a", 255);
			uint8_t r = color.getInt("r", 255);
			uint8_t g = color.getInt("g", 255);
			uint8_t b = color.getInt("b", 255);
			bg.color = rtype::ecs::Color(a, r, g, b);
		}
		else
			bg.color = rtype::ecs::Color(255, 255, 255, 255);

		_backgrounds.push_back(std::move(bg));
	}
}

void BackgroundComponent::start()
{
	if (!gameEngine().hasGraphics()) return;

	for (auto& bg : _backgrounds)
	{
		bg.size = static_cast<float>(gameEngine().getGraphics().getSize(bg.sprite).x);
	}
}

void BackgroundComponent::update()
{
	if (!gameEngine().hasGraphics()) return;

	for (auto& bg : _backgrounds)
	{
		bg.pos -= bg.speed * gameEngine().getElapsedTime();
		if (bg.pos < -bg.size)
			bg.pos += bg.size;
		else if (bg.pos > bg.size)
			bg.pos -= bg.size;
	}
}

void BackgroundComponent::draw()
{
	for (auto& bg : _backgrounds)
	{
		gameEngine().getGraphics().draw(bg.sprite,
			rtype::ecs::Vector3f(bg.pos, 0.0f, 0.0f),
			rtype::ecs::IntRect(),
			rtype::ecs::Vector2f(1.0f, 1.0f),
			bg.color);

		if (bg.speed > 0)
			gameEngine().getGraphics().draw(bg.sprite,
				rtype::ecs::Vector3f(bg.pos + bg.size, 0.0f, 0.0f),
				rtype::ecs::IntRect(),
				rtype::ecs::Vector2f(1.0f, 1.0f),
				bg.color);
		else
			gameEngine().getGraphics().draw(bg.sprite,
				rtype::ecs::Vector3f(bg.pos - bg.size, 0.0f, 0.0f),
				rtype::ecs::IntRect(),
				rtype::ecs::Vector2f(1.0f, 1.0f),
				bg.color);
	}
}
