#ifndef RTYPE_LIBRARY_LIBRARYMANAGER_HPP_
#define RTYPE_LIBRARY_LIBRARYMANAGER_HPP_

#include <string>
#include <unordered_map>
#include <memory>

#include "RType/Library/LibraryLoader.hpp"
#include "RType/Library/LibraryError.hpp"
#include "RType/System/NonCopyable.hpp"

namespace rtype
{
	namespace library
	{
		class LibraryManager
		{
		private:
			std::unordered_map<std::string, std::unique_ptr<ALibraryLoader>> _plugins;

		public:
			template <typename T>
			T* instantiate(const std::string& plugin)
			{
				ALibraryLoader* loader = getLoader(plugin);
				T* instance = loader->instantiate<T>();
				if (!instance)
					throw LibraryError("Could not cast plugin " + plugin + " into the requested type.");
				return instance;
			}
		private:
			ALibraryLoader* getLoader(const std::string& plugin);
			void loadPlugin(const std::string& plugin);
		};
	} // namespace library
} // namespace rtype

#endif // RTYPE_LIBRARY_LIBRARYMANAGER_HPP_
