#ifndef SOUNDPLAYERCOMPONENT_HPP_
#define SOUNDPLAYERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class SoundPlayerComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::string _file;
	float _volume;

public:
	virtual ~SoundPlayerComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
};

#endif // !SOUNDPLAYERCOMPONENT_HPP_
