#include <iostream>
#include "RType/Library/LibraryManager.hpp"

namespace rtype
{
	namespace library
	{
		ALibraryLoader* LibraryManager::getLoader(const std::string& plugin)
		{
			auto it = _plugins.find(plugin);
			if (it == _plugins.end())
			{
				loadPlugin(plugin);
				it = _plugins.find(plugin);
				if (it == _plugins.end())
					throw LibraryError("Could not load or find plugin " + plugin);
			}
			return (it->second).get();
		}

		void LibraryManager::loadPlugin(const std::string& plugin)
		{
			const std::string directory = "plugins";

			std::unique_ptr<LibraryLoader> library(new LibraryLoader(directory, plugin));
			_plugins[plugin] = std::move(library);
		}

	} // namespace library
} // namespace rtype
