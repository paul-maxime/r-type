#ifndef RTYPE_SERVER_ASYNCUDPSERVER_HPP_
#define RTYPE_SERVER_ASYNCUDPSERVER_HPP_

#include <cstdint>
#include <string>

#include "RType/Network/UdpSocket.hpp"
#include "RType/Server/ThreadPool.hpp"

namespace rtype
{
	namespace server
	{
		class AsyncUdpServer
		{
		private:
			ThreadPool _pool;
			network::UdpSocket _udp;
			std::function<void (const std::string&, uint16_t, const std::string&)> _callback;

		public:
			AsyncUdpServer(size_t threadCount);

			ThreadPool& pool();
			network::UdpSocket& udp();

			void bind(uint16_t port,
					  const std::function<void (const std::string& ip,
												uint16_t port,
												const std::string& content)>&
					  callback);

		private:
			void receivePacket();
		};
	} // namespace server
} // namespace rtype

#endif // RTYPE_SERVER_ASYNCUDPSERVER_HPP_
