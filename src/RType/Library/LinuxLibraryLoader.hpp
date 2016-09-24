#ifndef RTYPE_LIBRARY_LINUXLIBRARYLOADER_HPP_
#define RTYPE_LIBRARY_LINUXLIBRARYLOADER_HPP_

#include <string>

#include "RType/Library/ALibraryLoader.hpp"

namespace rtype
{
	namespace library
	{
		class LinuxLibraryLoader : public ALibraryLoader
		{
		private:
			void *_handle;
			InstantiateFct _fct;

		public:
			LinuxLibraryLoader(const std::string& directory, const std::string& filename);
			virtual ~LinuxLibraryLoader();

			virtual IPlugin* getPlugin() const;
		};
	} // namespace library
} // namespace rtype

#endif // RTYPE_LIBRARY_LINUXLIBRARYLOADER_HPP_
