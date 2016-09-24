#include <iomanip>
#include <stdexcept>
#include <sstream>

#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "TimeHUDComponent.hpp"

RTYPE_COMPONENT_IMPL(TimeHUDComponent)

void TimeHUDComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_circle = file.getString("circle");
	_littleCircle = file.getString("littleCircle");
}

void TimeHUDComponent::start()
{
	auto renderer = gameObject().getComponent<ITextRenderer>();
	auto transform = gameObject().getComponent<ITransform>();

	if (!renderer || !transform)
		throw std::runtime_error("A time without a TextRenderer and a Transform is not even possible.");
	_renderer = renderer;
	_pos = transform->getPosition();
	_timer = 0.0f;
	_rota = 0.0f;
	setText();
}

void TimeHUDComponent::update()
{
	_timer += gameEngine().getElapsedTime();
	_rota += 20.0f * gameEngine().getElapsedTime();
	setText();
}

void TimeHUDComponent::draw()
{
	gameEngine().getGraphics().draw(_circle,
		_pos,
		rtype::ecs::IntRect(), rtype::ecs::Vector2f(0.5f, 0.5f),
		rtype::ecs::Color(255, 255, 255, 255), 2.0f * _rota,
		rtype::ecs::Vector2f(155.0f, 155.5f));
	gameEngine().getGraphics().draw(_littleCircle,
		_pos,
		rtype::ecs::IntRect(), rtype::ecs::Vector2f(0.5f, 0.5f),
		rtype::ecs::Color(255, 255, 255, 255), -_rota,
		rtype::ecs::Vector2f(103.0f, 103.0f));
}

void TimeHUDComponent::setText()
{
	if (!gameEngine().hasGraphics()) return;

	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(7) <<	std::fixed << std::setprecision(3) << _timer;

	std::string	str = oss.str();
	std::replace(str.begin(), str.end(), '.', '\n');
	auto renderer = _renderer.lock();
	if (renderer)
	{
		renderer->setText(str);
	}
}
