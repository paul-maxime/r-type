#include "RType/ECS/GameEngine.hpp"
#include "Components/AudioSource/IAudioSource.hpp"
#include "SoundPlayerComponent.hpp"

RTYPE_COMPONENT_IMPL(SoundPlayerComponent)

void SoundPlayerComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_file = file.getString("file");
	_volume = file.getFloat("volume", 50.0f);
}

void SoundPlayerComponent::start()
{
	if (gameEngine().hasGraphics() && _file != "")
	{
		auto audio = gameObject().getComponent<IAudioSource>();
		if (audio)
		{
			audio->playSound(_file, _volume);
		}
	}
}
