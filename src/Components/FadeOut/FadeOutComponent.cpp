#include "RType/ECS/GameObject.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "Components/Animations/AnimationsComponent.hpp"
#include "FadeOutComponent.hpp"

RTYPE_COMPONENT_IMPL(FadeOutComponent)

void FadeOutComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_fadeAnimation = file.getString("fade_out_animation", "fade");
	_endAnimation = file.getString("end_animation", "end");
	_duration = file.getFloat("duration", 1.f);
}

void FadeOutComponent::start()
{
	_timer = 0;
}

void FadeOutComponent::update()
{
	if (!gameObject().isLocal()) return;

	_timer += gameEngine().getElapsedTime();

	auto a = gameObject().getComponent<IAnimations>();

	if (a)
	{
		float time = a->getAnimationDuration(_fadeAnimation);
		if (!a->willPlay(_fadeAnimation) && !a->willPlay(_endAnimation) &&
			_duration - _timer <= time)
		{
			a->setAnim(_fadeAnimation);
			a->queueAnim(_endAnimation);
		}
	}
	if (_timer >= _duration)
		gameObject().destroy();
}

float FadeOutComponent::getDuration() const
{
	return (_duration);
}
