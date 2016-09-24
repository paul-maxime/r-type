#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "RType/Network/LinuxUdpSocket.hpp"
#include "RType/Network/SocketError.hpp"

namespace rtype
{
	namespace network
	{
		LinuxUdpSocket::LinuxUdpSocket()
		{
			_fd = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (_fd == -1)
				throw SocketError("Could not create a new socket.");
		}

		LinuxUdpSocket::~LinuxUdpSocket()
		{
			if (::close(_fd) == -1)
				throw SocketError("Could not close the socket " + std::to_string(_fd));
		}

		void LinuxUdpSocket::bind(uint16_t port)
		{
			struct sockaddr_in sin = { AF_INET, htons(port), { htonl(INADDR_ANY) }, {0} };

			if (::bind(_fd, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin)) == -1)
			{
				throw SocketError("Could not bind the socket " + std::to_string(_fd) +
								  " to the port " + std::to_string(port));
			}
		}

		void LinuxUdpSocket::send(const std::string& ip, uint16_t port, const std::string& content)
		{
			struct sockaddr_in sin = { AF_INET, htons(port), {0}, {0} };

			if (inet_pton(AF_INET, ip.c_str(), &sin.sin_addr) <= 0)
				throw SocketError("Could not convert  " + ip + " as an IPv4.");

			if (::sendto(_fd, content.c_str(), content.size(), 0,
						 reinterpret_cast<struct sockaddr*>(&sin),
						 sizeof(sin)) != static_cast<ssize_t>(content.size()))
			{
				throw SocketError("Could not send " + std::to_string(content.size()) +
								  "-bytes packet to " + ip + ":" + std::to_string(port));
			}
		}

		void LinuxUdpSocket::recv(std::string& ip, uint16_t& port, std::string& content)
		{
			const size_t BUFFER_SIZE = 0xFFFF;
			const size_t ADDR_SIZE = 16;

			char buffer[BUFFER_SIZE];
			char addr[ADDR_SIZE];

			struct sockaddr_in sin;
			socklen_t sin_len = sizeof(sin);
			ssize_t size;

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

		bool LinuxUdpSocket::poll(uint32_t ms) const
		{
			struct pollfd pfd = { _fd, POLLIN, 0 };
			int result;

			if ((result = ::poll(&pfd, 1, ms)) == -1)
				throw SocketError("Could not poll socket " + std::to_string(_fd));

			return (result == 1);
		}
	}
}
