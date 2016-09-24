#include <iostream>

#include "EmptyPlugin.hpp"

EmptyPlugin::EmptyPlugin()
{
}

EmptyPlugin::~EmptyPlugin()
{
}

void EmptyPlugin::sayHello(IPlugin*)
{
	std::cout << "Hello, world." << std::endl;
}

void EmptyPlugin::sayNothing()
{
	std::cout << "Hello, empty world." << std::endl;
}

rtype::library::IPlugin* plugin_instantiate()
{
	return new EmptyPlugin();
}
