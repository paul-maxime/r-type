#include "RType/Server/User.hpp"

namespace rtype
{
	namespace server
	{
		User::User(const std::string& ip, uint16_t port, uint32_t id)
			: _ip(ip),
			  _port(port),
			  _id(id)
		{
		}

		const std::string& User::ip() const
		{
			return _ip;
		}

		uint16_t User::port() const
		{
			return _port;
		}

		uint32_t User::id() const
		{
			return _id;
		}

		void User::updateLag()
		{
			_lastUpdate = std::chrono::steady_clock::now();
		}

		float User::getLag() const
		{
			std::chrono::duration<float> secs =
				std::chrono::steady_clock::now() - _lastUpdate;

			return secs.count();
		}

		void User::addEntity(ecs::GameObject* entity)
		{
			_entities[entity->instanceId()] = entity;
		}

		ecs::GameObject* User::getEntity(uint32_t id) const
		{
			auto it = _entities.find(id);
			if (it != _entities.end())
				return it->second;
			return nullptr;
		}

		void User::destroyEntities()
		{
			for (auto& pair : _entities)
			{
				ecs::GameObject* object = pair.second;
				object->destroy();
			}
		}
	} // namespace server
} // namespace rtype
