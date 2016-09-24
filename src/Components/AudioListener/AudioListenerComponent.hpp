#ifndef AUDIOLISTENERCOMPONENT_HPP_
#define AUDIOLISTENERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class AudioListenerComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	float _volume;

public:
	virtual ~AudioListenerComponent() {}

	virtual void update();
};

#endif // !AUDIOLISTENERCOMPONENT_HPP_
