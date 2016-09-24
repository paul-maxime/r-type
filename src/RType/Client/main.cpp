#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#include "Client.hpp"
#include "RType/System/Chrono.hpp"

int main(int argc, char *argv[])
{
	try
	{
		rtype::client::Client client(std::vector<std::string>(&argv[1],
															  &argv[argc]));
	}
	catch (std::exception const & e)
	{
		std::cerr << std::chrono::system_clock::now() << " | "
				  << argv[0] << ": " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
