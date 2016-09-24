#include <iostream>
#include <unordered_set>
#include <sstream>
#include <stdexcept>

#include "RType/Client/AssetsManager.hpp"
#include "RType/Client/Client.hpp"
#include "RType/Client/SfmlGraphicsEngine.hpp"
#include "RType/Client/SfmlAudioEngine.hpp"
#include "RType/Client/SFMLInput.hpp"
#include "RType/ECS/GameObject.hpp"
#include "RType/System/BinaryReader.hpp"
#include "RType/Network/PacketReceiver.hpp"
#include "RType/Network/PacketSender.hpp"
#include "RType/Network/PacketFactory.hpp"
#include "RType/Network/Packets/UpdateEntities.hpp"
#include "RType/Network/SocketError.hpp"

namespace rtype
{
	namespace client
	{
		Client::Client(std::vector<std::string> const& args)
			: _inactivity(0)
		{
			system::random::init();
			network::PacketFactory::init();

			sf::RenderWindow window(sf::VideoMode(1024, 768), "R-Type v0.6");
#ifdef RTYPE_IS_LINUX
			window.setFramerateLimit(60);
#else
			window.setVerticalSyncEnabled(true);
#endif

			auto assets = std::unique_ptr<rtype::client::AssetsManager>(
				new rtype::client::AssetsManager("assets"));

			std::shared_ptr<rtype::ecs::IInput> inputs =
				std::make_shared<rtype::client::SFMLInput>(window);
			std::shared_ptr<rtype::ecs::IGraphicsEngine> graphics =
				std::make_shared<rtype::client::SfmlGraphicsEngine>(*assets, window, *inputs);
			std::shared_ptr<rtype::ecs::IAudioEngine> audio =
				std::make_shared<rtype::client::SfmlAudioEngine>(*assets);
			_network = std::make_shared<rtype::client::NetworkEngine>();


			_engine = std::unique_ptr<ecs::GameEngine>(
				new ecs::GameEngine(graphics, audio, inputs, _network));

			_udp.bind(0);

			if (args.size() == 1)
			{
				if (args[0] == "--local")
					_engine->loadScene("SinglePlayerScene");
				else
				{
					_engine->loadScene("MultiPlayerScene");
					_network->connect(args[0], 44321, 1012);
				}
			}
			else
				_engine->loadScene("MenuScene");

			while (window.isOpen())
			{
				handleNetwork();
				_engine->tick();
			}
		}

		void Client::handleNetwork()
		{
			if (!_network->isConnected() && !_network->isConnecting())
			{
				if (!_serializableEntities.empty())
					_serializableEntities.clear();
				while (_udp.poll(0))
					receivePacket();
				return;
			}

			while (_udp.poll(0))
			{
				try
				{
					_inactivity = 0;
					receivePacket();
				}
				catch (const network::SocketError&)
				{
					_inactivity = 1024;
				}
			}
			sendInputs();
			if (++_inactivity > 200)
			{
				_engine->loadScene("MenuScene");
				_network->disconnect();
				_serializableEntities.clear();
				_inactivity = 0;
			}
		}

		void Client::receivePacket()
		{
			std::string ip;
			uint16_t port;
			std::string content;
			_udp.recv(ip, port, content);

			if (!_network->isConnected() && !_network->isConnecting())
				return;

			if (!_network->isConnected())
			{
				_engine->clearScene();
				_network->setConnected();
				std::cout << "Connected to the server! " << ip << ":" << port << std::endl;
			}

			std::unordered_set<uint32_t> ids;
			for (const auto& gameObject : _engine->gameObjects())
			{
				if (!gameObject->isLocal())
					ids.emplace(gameObject->instanceId());
			}

			auto packet = std::unique_ptr<network::packets::APacket>
				(network::PacketReceiver::unpack(content));
			if (packet && packet->id() == network::packets::UpdateEntities::protocolId)
			{
				network::packets::UpdateEntities* updateEntities =
					static_cast<network::packets::UpdateEntities *>(packet.get());

				for (const auto& entity : updateEntities->entities())
				{
					ecs::GameObject* obj = _engine->getRemoteGameObject(entity.id());
					if (!obj)
					{
						obj = _engine->createRemoteGameObject(entity.originalName(),
							  entity.owner(), entity.id());
						if (entity.owner())
						{
							_serializableEntities.push_back(obj);
						}
					}
					obj->unserialize(entity);
					ids.erase(entity.id());
				}
			}

			for (uint32_t id : ids)
			{
				ecs::GameObject* obj = _engine->getRemoteGameObject(id);
				if (obj)
					obj->destroy();
				else
					std::cerr << "warning inexistant id " << id << std::endl;
			}
		}

		void Client::sendInputs()
		{
			network::packets::UpdateEntities update(_network->gameId());

			for (ecs::GameObject* object : _serializableEntities)
			{
				network::types::Entity entity;
				object->serialize(entity);
				update.entities().push_back(std::move(entity));
			}

			std::string packet = network::PacketSender::pack(update);

			_udp.send(_network->host(), _network->port(), packet);
		}
	} // namespace client
} // namespace rtype
