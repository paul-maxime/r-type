#ifndef RTYPE_NETWORK_IUDPSOCKET_HPP_
#define RTYPE_NETWORK_IUDPSOCKET_HPP_

#include <cstdint>
#include <string>

#include "RType/System/NonCopyable.hpp"

namespace rtype
{
	namespace network
	{
		class IUdpSocket : public system::NonCopyable
		{
		public:
			virtual ~IUdpSocket() {}

			virtual void bind(uint16_t port) = 0;
			virtual void send(const std::string& ip, uint16_t port, const std::string& content) = 0;
			virtual void recv(std::string& ip, uint16_t& port, std::string& content) = 0;
			virtual bool poll(uint32_t ms) const = 0;
		};
	} // namespace network
} // namespace rType

#endif // RTYPE_NETWORK_IUDPSOCKET_HPP_
