#include <dlfcn.h>

#include "RType/Library/LinuxLibraryLoader.hpp"
#include "RType/Library/LibraryError.hpp"

namespace rtype
{
	namespace library
	{
		LinuxLibraryLoader::LinuxLibraryLoader(const std::string& directory, const std::string& filename)
		{
			std::string fullname = directory + "/lib" + filename + ".so";

			_handle = dlopen(fullname.c_str(), RTLD_NOW | RTLD_GLOBAL);
			if (!_handle)
				throw LibraryError("Could not load library " + fullname + ":\n" +
								   dlerror());

			void* addr = dlsym(_handle, "plugin_instantiate");
			if (!addr)
				throw LibraryError("Could not get plugin_instantiate entrypoint from " +
								   filename + "\n: " + dlerror());
			_fct = reinterpret_cast<InstantiateFct>(addr);
		}

		LinuxLibraryLoader::~LinuxLibraryLoader()
		{
			dlclose(_handle);
		}

		IPlugin* LinuxLibraryLoader::getPlugin() const
		{
			return _fct();
		}
	}
}
