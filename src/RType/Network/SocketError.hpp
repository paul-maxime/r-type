#ifndef RTYPE_NETWORK_SOCKETERROR_HPP_
#define RTYPE_NETWORK_SOCKETERROR_HPP_

#include <stdexcept>
#include <string>

namespace rtype
{
	namespace network
	{
		class SocketError : public std::runtime_error
		{
		public:
			SocketError(const std::string& message);
			virtual ~SocketError() throw();
		};
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_SOCKETERROR_HPP_
