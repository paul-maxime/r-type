#ifndef RTYPE_SERVER_USER_HPP_
#define RTYPE_SERVER_USER_HPP_

#include <chrono>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "RType/ECS/GameObject.hpp"

namespace rtype
{
	namespace server
	{
		class User
		{
		private:
			std::string _ip;
			uint16_t _port;
			uint32_t _id;
			std::chrono::steady_clock::time_point _lastUpdate;
			std::unordered_map<uint32_t, ecs::GameObject *> _entities;

		public:
			User(const std::string& ip, uint16_t port, uint32_t id);

			const std::string& ip() const;
			uint16_t port() const;
			uint32_t id() const;

			void updateLag();
			float getLag() const;

			void addEntity(ecs::GameObject* entity);
			ecs::GameObject* getEntity(uint32_t id) const;
			void destroyEntities();
		};
	} // namespace server
} // namespace rtype

#endif // RTYPE_SERVER_USER_HPP_
