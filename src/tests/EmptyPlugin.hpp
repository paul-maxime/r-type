#ifndef EMPTYPLUGIN_HPP_
#define EMPTYPLUGIN_HPP_

#include "IHelloPlugin.hpp"

RTYPE_PLUGIN
class EmptyPlugin : public IHelloPlugin
{
public:
	EmptyPlugin();
	virtual ~EmptyPlugin();
	virtual void sayHello(IPlugin*);

	virtual void sayNothing();
};

#endif
