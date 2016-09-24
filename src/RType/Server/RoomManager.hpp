#ifndef RTYPE_SERVER_ROOMMANAGER_HPP_
#define RTYPE_SERVER_ROOMMANAGER_HPP_

#include <memory>
#include <mutex>
#include <unordered_map>

#include "RType/Server/AsyncUdpServer.hpp"
#include "RType/Server/Room.hpp"
#include "RType/System/NonCopyable.hpp"

namespace rtype
{
	namespace server
	{
		class RoomManager
		{
			AsyncUdpServer& _server;
			std::unordered_map<size_t, std::unique_ptr<Room>> _rooms;
			std::mutex _mutex;

		public:
			RoomManager(AsyncUdpServer& pool);

		public:
			Room& getRoom(size_t roomID);
			size_t roomsCount() const;

		private:
			void resizePool();
			void triggerUpdate();
			void updateRooms();
		};

	} // namespace server
} // namespace rtype

#endif // !RTYPE_SERVER_ROOMMANAGER_HPP_
