#ifndef AUDIOSOURCECOMPONENT_HPP_
#define AUDIOSOURCECOMPONENT_HPP_

#include <string>

#include "RType/ECS/GameEngine.hpp"
#include "RType/ECS/AComponent.hpp"
#include "IAudioSource.hpp"

RTYPE_PLUGIN
class AudioSourceComponent : public rtype::ecs::AComponent, public IAudioSource
{
	RTYPE_COMPONENT

private:
	bool _isSpacial;
	float _minDistance;
	float _attenuation;

public:
	virtual ~AudioSourceComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);

	virtual void playSound(const std::string& sound, float volume) const;
};

#endif // !AUDIOSOURCECOMPONENT_HPP_
