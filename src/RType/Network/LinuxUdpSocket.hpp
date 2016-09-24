#ifndef RTYPE_NETWORK_LINUXUDPSOCKET_HPP_
#define RTYPE_NETWORK_LINUXUDPSOCKET_HPP_

#include "RType/Network/IUdpSocket.hpp"

namespace rtype
{
	namespace network
	{
		class LinuxUdpSocket : public IUdpSocket
		{
		private:
			int _fd;

		public:
			LinuxUdpSocket();
			virtual ~LinuxUdpSocket();

			virtual void bind(uint16_t port);
			virtual void send(const std::string& ip, uint16_t port, const std::string& content);
			virtual void recv(std::string& ip, uint16_t& port, std::string& content);
			virtual bool poll(uint32_t ms) const;
		};
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_LINUXUDPSOCKET_HPP_
