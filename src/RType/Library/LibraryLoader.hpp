#ifndef RTYPE_LIBRARY_LIBRARYLOADER_HPP_
#define RTYPE_LIBRARY_LIBRARYLOADER_HPP_

#ifdef RTYPE_IS_UNIX

# include "LinuxLibraryLoader.hpp"

namespace rtype
{
	namespace library
	{
		typedef LinuxLibraryLoader LibraryLoader;
	}
}

#elif RTYPE_IS_WIN32

# include "WindowsLibraryLoader.hpp"

namespace rtype
{
	namespace library
	{
		typedef WindowsLibraryLoader LibraryLoader;
	}
}

#else
# error operating system not supported (LibraryLoader)
#endif

#endif // RTYPE_LIBRARY_LIBRARYLOADER_HPP_
