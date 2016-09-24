#include "RType/System/EndOfStreamError.hpp"

namespace rtype
{
	namespace system
	{
		EndOfStreamError::EndOfStreamError()
			: runtime_error("Reached the end of a binary stream")
		{
		}

		EndOfStreamError::~EndOfStreamError() throw()
		{
		}
	}
}
