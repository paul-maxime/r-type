#ifndef IPLAYERCOLORIZECOMPONENT_HPP_
#define IPLAYERCOLORIZECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

class IPlayerColorize
{
private:

public:
	virtual void loadFile(const rtype::ecs::file::Value&) = 0;
	virtual void start() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

	virtual uint8_t sprite(size_t id, size_t size) = 0;
};

#endif // !IPLAYERCOLORIZECOMPONENT_HPP_
