#include <functional>
#include "RType/Server/AsyncUdpServer.hpp"
#include "RType/Network/SocketError.hpp"

namespace rtype
{
	namespace server
	{
		AsyncUdpServer::AsyncUdpServer(size_t threadCount)
			: _pool(threadCount)
		{
		}

		ThreadPool& AsyncUdpServer::pool()
		{
			return _pool;
		}

		network::UdpSocket& AsyncUdpServer::udp()
		{
			return _udp;
		}

		void AsyncUdpServer::bind(uint16_t port,
								  const std::function<void (const std::string& ip,
															uint16_t port,
															const std::string& content)>&
								  callback)
		{
			_udp.bind(port);
			_callback = callback;
			_pool.add(std::bind(&AsyncUdpServer::receivePacket, this));
		}

		void AsyncUdpServer::receivePacket()
		{
			_udp.poll(-1);

			try
			{
				std::string ip;
				uint16_t port;
				std::string content;

				_udp.recv(ip, port, content);
				_pool.add(std::bind(&AsyncUdpServer::receivePacket, this));
				_callback(ip, port, content);
			}
			catch (const network::SocketError&)
			{
				_pool.add(std::bind(&AsyncUdpServer::receivePacket, this));
			}
		}
	} // namespace server
} // namespace rtype
