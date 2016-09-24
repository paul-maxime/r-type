#include <iomanip>
#include <stdexcept>
#include <sstream>

#include "RType/ECS/GameEngine.hpp"
#include "ScoreComponent.hpp"

RTYPE_COMPONENT_IMPL(ScoreComponent)

ScoreComponent::ScoreComponent() :
_score(0)
{
}

void ScoreComponent::start()
{
	auto renderer = gameObject().getComponent<ITextRenderer>();
	if (!renderer)
		throw std::runtime_error("A score without a TextRenderer is not even possible.");
	_renderer = renderer;

	setText();
}

void ScoreComponent::serialize(rtype::system::BinaryWriter& writer)
{
	writer << _score;
}

void ScoreComponent::unserialize(rtype::system::BinaryReader& reader)
{
	uint32_t score;
	reader >> score;
	if (score != _score)
	{
		_score = score;
		setText();
	}
}

void ScoreComponent::add(uint32_t score)
{
	_score += score;
	setText();
}

void ScoreComponent::setText()
{
	if (!gameEngine().hasGraphics()) return;

	std::ostringstream oss;
	oss /*<< "Score: " */ << std::setfill('0') << std::setw(8) << _score;

	auto renderer = _renderer.lock();
	if (renderer)
	{
		renderer->setText(oss.str());
	}
}
