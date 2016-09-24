#ifndef ADVANCEDPLUGIN_HPP_
#define ADVANCEDPLUGIN_HPP_

#include "IHelloPlugin.hpp"

RTYPE_PLUGIN
class AdvancedPlugin : public IHelloPlugin
{
public:
	AdvancedPlugin();
	virtual ~AdvancedPlugin();
	virtual void sayHello(IPlugin*);
};

#endif
