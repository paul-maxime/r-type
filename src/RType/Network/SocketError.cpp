#include "RType/Network/SocketError.hpp"

namespace rtype
{
	namespace network
	{
		SocketError::SocketError(const std::string& message)
			: runtime_error(message)
		{
		}

		SocketError::~SocketError() throw()
		{
		}
	}
}
