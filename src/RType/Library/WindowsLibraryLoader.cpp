#include <iostream>
#include <Windows.h>

#include "RType/Library/WindowsLibraryLoader.hpp"
#include "RType/Library/LibraryError.hpp"

namespace rtype
{
	namespace library
	{
		WindowsLibraryLoader::WindowsLibraryLoader(const std::string& directory, const std::string& filename)
		{
			std::string fullname = directory + "/" + filename + ".dll";

			_handle = LoadLibrary(fullname.c_str());
			if (!_handle)
				throw LibraryError("Could not load library " + fullname + ":" + std::to_string(GetLastError()));

			void* addr = GetProcAddress(reinterpret_cast<HMODULE>(_handle), "plugin_instantiate");
			if (!addr)
				throw LibraryError("Could not get plugin_instantiate entrypoint from " + filename + ": " + std::to_string(GetLastError()));
			_fct = reinterpret_cast<InstantiateFct>(addr);
		}

		WindowsLibraryLoader::~WindowsLibraryLoader()
		{
			/*if (!FreeLibrary(reinterpret_cast<HMODULE>(_handle)))
			{
				std::cerr << "Could not free library!" << std::endl;
			}*/
		}

		IPlugin* WindowsLibraryLoader::getPlugin() const
		{
			return _fct();
		}
	}
}
