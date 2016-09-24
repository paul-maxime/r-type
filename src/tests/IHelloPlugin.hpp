#ifndef IHELLOPLUGIN_HPP_
#define IHELLOPLUGIN_HPP_

#include "RType/Library/IPlugin.hpp"

class IHelloPlugin : public rtype::library::IPlugin
{
public:
	virtual ~IHelloPlugin() {}
	virtual void sayHello(IPlugin*) = 0;
};

#endif
