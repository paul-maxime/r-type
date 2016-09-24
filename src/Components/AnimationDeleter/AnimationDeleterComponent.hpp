#ifndef ANIMATIONDELETERCOMPONENT_HPP_
#define ANIMATIONDELETERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class AnimationDeleterComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

public:
	virtual ~AnimationDeleterComponent() {}

	virtual void update();
};

#endif // !ANIMATIONDELETERCOMPONENT_HPP_
