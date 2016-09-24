#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Loader.hpp"

namespace rtype
{
	namespace ecs
	{
		namespace file
		{
			Loader::Loader(std::string const& component)
			{
				std::ifstream file(component);
				if (!file)
					throw std::runtime_error("Could not open file `" + component + "'");

				std::string fileContent((std::istreambuf_iterator<char>(file)),
					std::istreambuf_iterator<char>());

				Json::Reader reader;

				if (!reader.parse(fileContent, _entity))
				{
					throw std::runtime_error("Could not parse `" + component + "'\n"
						+ reader.getFormattedErrorMessages());
				}
			}

			std::vector<std::string> Loader::getComponents() const
			{
				return _entity.getMemberNames();
			}

			Value Loader::getComponent(std::string const & component) const
			{
				return Value(_entity[component]);
			}
		} // namespace file
	} // namespace ecs
} // namespace rtype
