#include <iostream>

#include "RType/Server/RoomManager.hpp"

namespace rtype
{
	namespace server
	{
		RoomManager::RoomManager(AsyncUdpServer& server)
			: _server(server)
		{
			triggerUpdate();
		}

		Room& RoomManager::getRoom(size_t roomID)
		{
			std::lock_guard<std::mutex> lock(_mutex);

			auto it = _rooms.find(roomID);
			if (it == _rooms.end())
			{
				std::cout << "[RoomManager] "
						  << "Creating room " << roomID << std::endl;
				std::unique_ptr<Room> room(new Room(roomID, _server));
				_rooms[roomID] = std::move(room);
				resizePool();
			}
			return *_rooms[roomID].get();
		}

		size_t RoomManager::roomsCount() const
		{
			return _rooms.size();
		}

		void RoomManager::triggerUpdate()
		{
			_server.pool().add(std::bind(&RoomManager::updateRooms, this));
		}

		void RoomManager::updateRooms()
		{
			std::lock_guard<std::mutex> lock(_mutex);

			for (auto it = _rooms.begin(); it != _rooms.end();)
			{
				auto& room = it->second;

				if (!room->isRunning())
				{
					it = _rooms.erase(it);
					resizePool();
				}
				else
					++it;
			}

			triggerUpdate();
		}

		void RoomManager::resizePool()
		{
			size_t threadCount = _rooms.size() / 4 + 1 + (_rooms.size() ? 1 : 0);
			if (_server.pool().size() != threadCount)
			{
				std::cout << "[RoomManager] "
						  << (_server.pool().size() < threadCount ? "Upgrading" : "Downgrading")
						  << " thread count to " << threadCount << std::endl;
				_server.pool().resize(threadCount);
			}
		}
	} // namespace server
} // namespace rtype
