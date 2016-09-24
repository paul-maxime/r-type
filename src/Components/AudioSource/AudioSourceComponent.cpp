#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "AudioSourceComponent.hpp"

RTYPE_COMPONENT_IMPL(AudioSourceComponent)

void AudioSourceComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_isSpacial = file.getBool("isSpacial");
	_minDistance = file.getFloat("minDistance", 1.0f);
	_attenuation = file.getFloat("attenuation", 0.0f);
}

void AudioSourceComponent::playSound(const std::string& sound, float volume) const
{
	if (!gameEngine().hasGraphics()) return;

	if (!_isSpacial)
		gameEngine().getAudio().playSound(sound, volume);
	else
	{
		auto transform = gameObject().getComponent<ITransform>();
		if (transform)
		{
			gameEngine().getAudio().playSound(sound, volume,
				transform->getAbsolutePosition(), _minDistance, _attenuation);
		}
	}
}
