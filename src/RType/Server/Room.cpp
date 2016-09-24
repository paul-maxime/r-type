#include <iostream>
#include <sstream>
#include <functional>

#include "RType/Network/UdpSocket.hpp"
#include "RType/Network/PacketSender.hpp"
#include "RType/Network/Packets/UpdateEntities.hpp"
#include "RType/Server/Room.hpp"

namespace rtype
{
	namespace server
	{
		Room::Room(uint32_t gameId, AsyncUdpServer& server)
			: _gameId(gameId),
			  _userIds(0),
			  _server(server),
			  _isRunning(true),
			  _shouldStop(false),
			  _time(0.0f),
			  _lastTick(std::chrono::steady_clock::now())
		{
			std::lock_guard<std::mutex> lock(_mutex);

			_game.createGameObject("GameScene");
			triggerUpdate();
		}

		void Room::name(std::string const & name)
		{
			_name = name;
		}

		std::string const & Room::name() const
		{
			return _name;
		}

		void Room::stop()
		{
			std::cout << "[" << _gameId << "]: stopping the room"
					  << std::endl;
			_shouldStop = true;
		}

		bool Room::isRunning() const
		{
			return _isRunning;
		}

		void Room::onPacketReceived(const std::string& ip,
			uint16_t port,
			network::packets::UpdateEntities* packet)
		{
			std::lock_guard<std::mutex> lock(_mutex);

			if (!_isRunning) return;

			User* user = getUser(ip, port);
			if (!user)
			{
				addUser(ip, port);
				user = getUser(ip, port);
			}
			if (user)
			{
				user->updateLag();
				for (auto& entity : packet->entities())
				{
					ecs::GameObject* obj = user->getEntity(entity.id());
					if (obj && obj->isOwner())
					{
						entity.owner(false);
						obj->unserialize(entity);
					}
				}
			}
		}

		void Room::update()
		{
			std::lock_guard<std::mutex> lock(_mutex);

			updateGame();
			if (_isRunning)
				triggerUpdate();
		}

		void Room::updateGame()
		{
			using namespace std::chrono;

			float time = static_cast<float>
				(duration_cast<milliseconds>
					(steady_clock::now() - _lastTick).count());

			bool hasUpdated = false;

			while (_time + time > 16.f)
			{
				_game.tick();
				time -= 16.f;
				_time += time;
				hasUpdated = true;
				_lastTick = steady_clock::now();
			}
			if (hasUpdated)
			{
				disconnectPlayers();
				sendEntities();
			}
		}

		void Room::triggerUpdate()
		{
			if (!_shouldStop)
			{
				_server.pool().add(std::bind(&Room::update, this));
			}
			else
			{
				_isRunning = false;
			}
		}

		void Room::disconnectPlayers()
		{
			for (auto it = _users.begin(); it != _users.end();)
			{
				auto& user = *it;
				if (user->getLag() > 2.0f)
				{
					std::cout << "[" << _gameId << "]: disconnecting inactive user"
							  << " (" << user->ip() << ":" << user->port() << ")"
							  << std::endl;

					user->destroyEntities();

					it = _users.erase(it);
				}
				else
					++it;
			}
			if (_users.size() == 0)
				stop();
		}

		void Room::sendEntities()
		{
			for (auto& user : _users)
			{
				sendEntities(user.get());
			}
		}

		void Room::sendEntities(const User* user)
		{
			network::packets::UpdateEntities update(_gameId);

			for (auto const & object : _game.gameObjects())
			{
				network::types::Entity entity;
				object->serialize(entity);
				entity.owner(!!user->getEntity(object->instanceId()) && object->isOwner());
				update.entities().push_back(std::move(entity));
			}

			std::string packet = network::PacketSender::pack(update);

			if (packet.size() > 20000)
			{
				std::cerr << "Warning: critical packet size! (" << packet.size() << ")" << std::endl;
			}

			_server.pool()
				.add(std::bind(&network::UdpSocket::send,
						&_server.udp(),
						user->ip(), user->port(), packet));
		}

		void Room::addUser(const std::string& ip, uint16_t port)
		{
			if (_users.size() < Room::MAX_USERS)
			{
				std::cout << "[" << _gameId << "]: adding a new user"
						  << " (" << ip << ":" << port << ")" << std::endl;


				auto user = std::unique_ptr<User>(new User(ip, port, ++_userIds));

				ecs::GameObject* player = _game.createGameObject("Player");
				player->name("Player" + std::to_string(user->id()));
				player->setNetwork(true, false);
				user->addEntity(player);

				ecs::GameObject* inputs = _game.createGameObject("PlayerInputs");
				inputs->name("Player" + std::to_string(user->id()) + "Inputs");
				inputs->setNetwork(true, true);
				user->addEntity(inputs);

				_users.push_back(std::move(user));
			}
		}

		User* Room::getUser(const std::string& ip, uint16_t port) const
		{
			for (auto& user : _users)
			{
				if (user->ip() == ip && user->port() == port)
					return (user.get());
			}
			return (0);
		}
	} // namespace server
} // namespace rtype
