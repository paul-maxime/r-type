#include <iostream>

#include "RType/Library/LibraryManager.hpp"
#include "IHelloPlugin.hpp"

int	main()
{
	try
	{
		rtype::library::LibraryManager libs;

		IHelloPlugin* pl = libs.instantiate<IHelloPlugin>("emptyplugin");
		IHelloPlugin* pl2 = libs.instantiate<IHelloPlugin>("advancedplugin");
		pl2->sayHello(pl);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
	}
}
