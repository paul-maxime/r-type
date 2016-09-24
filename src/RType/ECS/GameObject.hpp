#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <list>
#include <functional>
#include <memory>

#include "RType/ECS/AComponent.hpp"
#include "RType/Network/Types/Entity.hpp"

namespace rtype
{
	namespace ecs
	{
		class GameEngine;

		class GameObject
		{
		public:
			GameObject(unsigned int, rtype::ecs::GameEngine &, const std::string &);
			GameObject(GameObject const &);

		private:
			size_t _instanceId;
			GameEngine& _engine;
			bool _isLocal;
			bool _isOwner;

			std::string _name;
			std::string _originalName;

			std::list<std::shared_ptr<AComponent>> _components;

			bool _started;
			bool _stopped;
			bool _enabled;
			bool _destroyed;

			int32_t _layer;

		public:
			size_t instanceId() const;
			void instanceId(size_t);

			void setNetwork(bool local, bool owner);
			bool isLocal() const;
			bool isOwner() const;

			void name(const std::string&);
			const std::string& name() const;

			void addComponent(std::string const&, file::Value const&);

			template <typename T>
			std::shared_ptr<T> getComponent() const;

			void loadFile(std::string const & file);

			void destroy();
			bool mustBeDeleted() const;

			void setEnabled(bool);
			bool enabled() const;

			void layer(int32_t value);
			int32_t layer() const;

			void start();
			void update();
			void lateUpdate();
			void onGUI();
			void draw();
			void stop();
			void serialize(network::types::Entity& entity);
			void unserialize(const network::types::Entity& entity);

		private:
			void addComponent(AComponent *);
		};

		template <typename T>
		std::shared_ptr<T> GameObject::getComponent() const
		{
			std::shared_ptr<T> obj;

			for (auto& e : _components)
			{
				obj = std::dynamic_pointer_cast<T>(e);
				if (obj)
					return (obj);
			}
			return (NULL);
		}

	} // namespace ecs
} // namespace rtype

#endif
