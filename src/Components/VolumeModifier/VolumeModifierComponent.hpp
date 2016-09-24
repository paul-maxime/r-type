#ifndef VOLUMEMODIFIERCOMPONENT_HPP_
#define VOLUMEMODIFIERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class VolumeModifierComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	rtype::ecs::IntRect	_rect;
	rtype::ecs::Vector3f _pos;
	float				_timeAxis;
public:
	virtual ~VolumeModifierComponent() {}

	virtual void start();
	virtual void update();

private:
	void setVolume(float volume);
};

#endif // !VOLUMEMODIFIERCOMPONENT_HPP_
