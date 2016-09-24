#include "RType/Library/LibraryError.hpp"

namespace rtype
{
	namespace library
	{
		LibraryError::LibraryError(const std::string& message)
			: runtime_error(message)
		{
		}

		LibraryError::~LibraryError() throw()
		{
		}
	}
}
