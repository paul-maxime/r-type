#include "RType/ECS/GameEngine.hpp"
#include "Components/TextRenderer/ITextRenderer.hpp"
#include "Components/Stage/IStage.hpp"
#include "StageNameComponent.hpp"

RTYPE_COMPONENT_IMPL(StageNameComponent)

void StageNameComponent::start()
{
	rtype::ecs::GameObject* obj = gameEngine().find("Stage");
	if (obj)
	{
		auto stage = obj->getComponent<IStage>();
		auto renderer = gameObject().getComponent<ITextRenderer>();
		if (stage)
		{
			renderer->setText(stage->name());
		}
	}
	_duration = 3.5f;
}

void StageNameComponent::update()
{
	if (!gameObject().isLocal()) return;

	_duration -= gameEngine().getElapsedTime();
	if (_duration < 0)
		gameObject().destroy();
}
