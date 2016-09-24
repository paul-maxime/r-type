#ifndef RTYPE_ECS_FILE_LOADER_HPP_
#define RTYPE_ECS_FILE_LOADER_HPP_

#include "RType/ECS/File/Value.hpp"
#include "json/reader.h"

namespace rtype
{
	namespace ecs
	{
		namespace file
		{
			class Loader
			{
			public:
				Loader(std::string const& component);

				std::vector<std::string> getComponents() const;
				Value getComponent(std::string const &component) const;

			private:
				Json::Value _entity;
			};
		} // namespace file
	} // namespace ecs
} // namespace rtype

#endif // !RTYPE_ECS_FILE_LOADER_HPP_
