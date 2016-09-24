#include "RType/ECS/GameEngine.hpp"
#include "MusicPlayerComponent.hpp"

RTYPE_COMPONENT_IMPL(MusicPlayerComponent)

void MusicPlayerComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_file = file.getString("file");
	_volume = file.getFloat("volume", 50.0f);
}

void MusicPlayerComponent::start()
{
	if (gameEngine().hasGraphics() && _file != "")
	{
		gameEngine().getAudio().playMusic(_file, _volume);
	}
}
