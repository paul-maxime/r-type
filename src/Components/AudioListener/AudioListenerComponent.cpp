#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "AudioListenerComponent.hpp"

RTYPE_COMPONENT_IMPL(AudioListenerComponent)

void AudioListenerComponent::update()
{
	if (!gameEngine().hasGraphics()) return;

	auto transform = gameObject().getComponent<ITransform>();

	if (transform)
	{
		gameEngine().getAudio().setListener(transform->getAbsolutePosition(),
			rtype::ecs::Vector3f(0.0f, -1.0f, 0.0f));
	}
}
