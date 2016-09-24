#ifndef HELLO_WORLD_COMPONENT_HPP_
#define HELLO_WORLD_COMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class HelloWorldComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::string _world;

public:
	virtual ~HelloWorldComponent();

	virtual void start();
	virtual void update();
	virtual void draw();
	virtual void loadFile(rtype::ecs::file::Value const &);
};

#endif // HELLO_WORLD_COMPONENT_HPP_
