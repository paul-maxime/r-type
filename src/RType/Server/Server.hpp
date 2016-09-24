#ifndef RTYPE_SERVER_SERVER_HPP_
#define RTYPE_SERVER_SERVER_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include "RType/System/NonCopyable.hpp"
#include "RType/Server/RoomManager.hpp"
#include "RType/Server/AsyncUdpServer.hpp"

namespace rtype
{
	namespace server
	{
		class Server : public system::NonCopyable
		{
		private:
			AsyncUdpServer _server;
			RoomManager _roomManager;

		public:
			Server(std::vector<std::string> const& arguments);

		private:
			void onReceivePacket(const std::string& ip,
				uint16_t port,
				const std::string& content);
		};
	} // namespace server
} // namespace rtype

#endif // !RTYPE_SERVER_SERVER_HPP_
