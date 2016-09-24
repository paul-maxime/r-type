#ifndef RTYPE_SERVER_ROOM_HPP_
#define RTYPE_SERVER_ROOM_HPP_

#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

#include "RType/ECS/GameEngine.hpp"
#include "RType/Server/AsyncUdpServer.hpp"
#include "RType/Server/User.hpp"
#include "RType/System/NonCopyable.hpp"
#include "RType/Network/Packets/UpdateEntities.hpp"

namespace rtype
{
	namespace server
	{
		class Room
		{
			const size_t MAX_USERS = 4;

			uint32_t _gameId;
			uint32_t _userIds;
			AsyncUdpServer& _server;
			ecs::GameEngine _game;
			std::string _name;
			std::mutex _mutex;
			bool _isRunning;
			bool _shouldStop;

			float _time;
			std::chrono::steady_clock::time_point _lastTick;

			std::vector<std::unique_ptr<User>> _users;

		public:
			Room(uint32_t gameId, AsyncUdpServer& server);

		public:
			void name(std::string const & name);
			std::string const & name() const;

			void stop();
			bool isRunning() const;

			void onPacketReceived(const std::string& ip,
								  uint16_t port,
								  network::packets::UpdateEntities* packet);

		private:
			void update();
			void updateGame();
			void triggerUpdate();
			void disconnectPlayers();
			void sendEntities();
			void sendEntities(const User* user);

			void addUser(const std::string& ip, uint16_t port);
			User* getUser(const std::string& ip, uint16_t port) const;
		};

	} // namespace server
} // namespace rtype

#endif // !RTYPE_SERVER_ROOM_HPP_
