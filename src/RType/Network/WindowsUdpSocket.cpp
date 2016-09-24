#include "RType/Network/WindowsUdpSocket.hpp"
#include "RType/Network/SocketError.hpp"

#pragma comment(lib, "Ws2_32.lib")

namespace rtype
{
	namespace network
	{
		bool WindowsUdpSocket::_initialized = false;
		WSADATA WindowsUdpSocket::_wsaData;

		WindowsUdpSocket::WindowsUdpSocket()
		{
			if (!_initialized)
			{
				if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0)
					throw SocketError("Could not initialize winsock 2.2");
				_initialized = true;
			}
			_fd = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (_fd == INVALID_SOCKET)
				throw SocketError("Could not create a new socket.");
		}

		WindowsUdpSocket::~WindowsUdpSocket()
		{
			if (::closesocket(_fd) != 0)
				throw SocketError("Could not close the socket " + std::to_string(_fd));
		}

		void WindowsUdpSocket::bind(uint16_t port)
		{
			SOCKADDR_IN sin = { AF_INET, htons(port) };
			sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

			if (::bind(_fd, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)) == -1)
			{
				throw SocketError("Could not bind the socket " + std::to_string(_fd) +
								  " to the port " + std::to_string(port));
			}
		}

		void WindowsUdpSocket::send(const std::string& ip, uint16_t port, const std::string& content)
		{
			SOCKADDR_IN sin = { AF_INET, htons(port) };

			if (inet_pton(AF_INET, ip.c_str(), &sin.sin_addr) <= 0)
				throw SocketError("Could not convert  " + ip + " as an IPv4.");

			if (::sendto(_fd, content.c_str(), content.size(), 0,
						 reinterpret_cast<struct sockaddr*>(&sin),
						 sizeof(sin)) != static_cast<int>(content.size()))
			{
				throw SocketError("Could not send " + std::to_string(content.size()) +
								  "-bytes packet to " + ip + ":" + std::to_string(port));
			}
		}

		void WindowsUdpSocket::recv(std::string& ip, uint16_t& port, std::string& content)
		{
			const size_t BUFFER_SIZE = 0xFFFF;
			const size_t ADDR_SIZE = 16;

			char buffer[BUFFER_SIZE];
			char addr[ADDR_SIZE];

			SOCKADDR_IN sin;
			socklen_t sin_len = sizeof(sin);
			int size;

			if ((size = ::recvfrom(_fd, buffer, sizeof(buffer), 0,
								   reinterpret_cast<struct sockaddr*>(&sin),
								   &sin_len)) == -1)
			{
				throw SocketError("Could not receive a packet on socket " +
								  std::to_string(_fd));
			}

			if (inet_ntop(AF_INET, &sin.sin_addr, addr, sizeof(addr)) == 0)
				throw SocketError("Could not convert sender into an ip address");

			ip = std::string(addr);
			port = ntohs(sin.sin_port);
			content = std::string(buffer, size);
		}

		bool WindowsUdpSocket::poll(uint32_t ms) const
		{
			struct pollfd pfd = { _fd, POLLIN, 0 };
			int result;

			if ((result = ::WSAPoll(&pfd, 1, ms)) == -1)
				throw SocketError("Could not poll socket " + std::to_string(_fd));

			return (result == 1);
		}
	}
}
