#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "Server.hpp"
#include "RType/System/Chrono.hpp"

int main(int argc, char *argv[])
{
	try
	{
		rtype::server::Server server(std::vector<std::string>(&argv[1],
															  &argv[argc]));
	}
	catch (std::exception const & e)
	{
		std::cerr << "[" << std::chrono::system_clock::now() << "] "
				  << "error in main thread:" << std::endl
				  << "	" << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
