#include "RType/ECS/GameObject.hpp"
#include "Components/Animations/IAnimations.hpp"
#include "AnimationDeleterComponent.hpp"

RTYPE_COMPONENT_IMPL(AnimationDeleterComponent)

void AnimationDeleterComponent::update()
{
	auto animations = gameObject().getComponent<IAnimations>();
	if (animations->hasPlayOnce())
	{
		if (gameObject().isLocal())
			gameObject().destroy();
		else
			gameObject().setEnabled(false);
	}
}
