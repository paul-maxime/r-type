#include <iostream>
#include "RType/ECS/GameEngine.hpp"
#include "HelloWorldComponent.hpp"

RTYPE_COMPONENT_IMPL(HelloWorldComponent)

HelloWorldComponent::~HelloWorldComponent()
{
	std::cerr << "Function #5 (destructor)" << std::endl;
}

void HelloWorldComponent::loadFile(rtype::ecs::file::Value const & file)
{
	std::cerr << "Excpecting functions to be called from #1 to #5 (quit normaly #5)" << std::endl;
	std::cerr << "Function #1 (loadFile)" << std::endl;
	_world = file.getString("world", "empty :(");
}

void HelloWorldComponent::start()
{
	std::cerr << "Function #2 (start)" << std::endl;
	std::cout << "HelloWorldComponent::start()" << std::endl;
	std::cout << "The World is " << _world << std::endl;
}

void HelloWorldComponent::update()
{
	static bool hasBeenThere = false;

	if (!hasBeenThere)
	{
		std::cerr << "Function #3 (update)" << std::endl;
		hasBeenThere = true;
	}
}

void HelloWorldComponent::draw()
{
	static bool hasBeenThere = false;

	if (!hasBeenThere)
	{
		std::cerr << "Function #4 (draw)" << std::endl;
		hasBeenThere = true;
	}
}
