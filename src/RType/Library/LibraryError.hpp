#ifndef RTYPE_LIBRARY_LIBRARYERROR_HPP_
#define RTYPE_LIBRARY_LIBRARYERROR_HPP_

#include <stdexcept>
#include <string>

namespace rtype
{
	namespace library
	{
		class LibraryError : public std::runtime_error
		{
		public:
			LibraryError(const std::string& message);
			virtual ~LibraryError() throw();
		};
	} // namespace library
} // namespace rType

#endif // RTYPE_LIBRARY_LIBRARYERROR_HPP_
