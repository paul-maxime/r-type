#include <iostream>

#include "EmptyPlugin.hpp"
#include "AdvancedPlugin.hpp"

AdvancedPlugin::AdvancedPlugin()
{
}

AdvancedPlugin::~AdvancedPlugin()
{
}

void AdvancedPlugin::sayHello(IPlugin* plugin)
{
	std::cout << "Hello from advanced world." << std::endl;
	static_cast<EmptyPlugin*>(plugin)->sayNothing();
}

rtype::library::IPlugin* plugin_instantiate()
{
	return new AdvancedPlugin();
}
