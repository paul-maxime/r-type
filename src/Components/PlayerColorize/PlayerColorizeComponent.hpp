#ifndef PLAYERCOLORIZECOMPONENT_HPP_
#define PLAYERCOLORIZECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "IPlayerColorize.hpp"

RTYPE_PLUGIN
class PlayerColorizeComponent : public rtype::ecs::AComponent, public IPlayerColorize
{
	RTYPE_COMPONENT

private:
	std::unordered_map<size_t, size_t> _taken;
	std::vector<std::string> _shipName;


public:
	virtual ~PlayerColorizeComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void draw();

	virtual uint8_t sprite(size_t id, size_t size);
};

#endif // !PLAYERCOLORIZECOMPONENT_HPP_
