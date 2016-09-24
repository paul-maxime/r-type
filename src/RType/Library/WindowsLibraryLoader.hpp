#ifndef RTYPE_LIBRARY_WINDOWSLIBRARYLOADER_HPP_
#define RTYPE_LIBRARY_WINDOWSLIBRARYLOADER_HPP_

#include <string>

#include "RType/Library/ALibraryLoader.hpp"

namespace rtype
{
	namespace library
	{
		class WindowsLibraryLoader : public ALibraryLoader
		{
		private:
			void* _handle;
			InstantiateFct _fct;

		public:
			WindowsLibraryLoader(const std::string& directory, const std::string& filename);
			virtual ~WindowsLibraryLoader();

			virtual IPlugin* getPlugin() const;
		};
	} // namespace library
} // namespace rtype

#endif // RTYPE_LIBRARY_WINDOWSLIBRARYLOADER_HPP_
