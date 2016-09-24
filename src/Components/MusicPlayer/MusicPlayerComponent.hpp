#ifndef MUSICPLAYERCOMPONENT_HPP_
#define MUSICPLAYERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class MusicPlayerComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::string _file;
	float _volume;

public:
	virtual ~MusicPlayerComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
};

#endif // !MUSICPLAYERCOMPONENT_HPP_
