#include <fstream>
#include <iostream>
#include <algorithm>

#include "RType/ECS/File/Loader.hpp"

void printName(std::string const & name)
{
	std::cout << '\t' << name << std::endl;
}

void testLoader(std::string const & entity)
{
	rtype::ecs::file::Loader loader(entity);

	std::cout << "Components of the entity:" << std::endl;

	std::vector< std::string > components = loader.getComponents();
	for (std::string & e : components)
	{
		printName(e);
	}


	rtype::ecs::file::Value sprite = loader.getComponent("SpriteRenderer");

	std::string path = sprite.getString("image");
	std::cout << path << std::endl << std::endl;

	std::cout << "Test successful" << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	testLoader(argv[1]);
	return 0;
}
