#ifndef RTYPE_NETWORK_WINDOWSUDPSOCKET_HPP_
#define RTYPE_NETWORK_WINDOWSUDPSOCKET_HPP_

#include <winsock2.h>
#include <ws2tcpip.h>

#include "RType/Network/IUdpSocket.hpp"

namespace rtype
{
	namespace network
	{
		class WindowsUdpSocket : public IUdpSocket
		{
		private:
			static bool _initialized;
			static WSADATA _wsaData;

			SOCKET _fd;

		public:
			WindowsUdpSocket();
			virtual ~WindowsUdpSocket();

			virtual void bind(uint16_t port);
			virtual void send(const std::string& ip, uint16_t port, const std::string& content);
			virtual void recv(std::string& ip, uint16_t& port, std::string& content);
			virtual bool poll(uint32_t ms) const;
		};
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_WINDOWSUDPSOCKET_HPP_
