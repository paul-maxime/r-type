#include <iostream>
#include <sstream>

#include "RType/ECS/GameEngine.hpp"
#include "RType/ECS/GameObject.hpp"
#include "RType/ECS/File/Loader.hpp"

namespace rtype
{
	namespace ecs
	{
		GameObject::GameObject(
			unsigned int instanceId,
			GameEngine &engine,
			const std::string& name) :
			_instanceId(instanceId),
			_engine(engine),
			_isLocal(true),
			_isOwner(false),
			_name(name),
			_originalName(name),
			_started(false),
			_stopped(false),
			_enabled(true),
			_destroyed(false),
			_layer(0)
		{
			size_t pos = _name.find('/');
			if (pos != std::string::npos)
				_name = _name.substr(pos + 1);
		}

		GameObject::GameObject(GameObject const & obj) :
			_instanceId(0),
			_engine(obj._engine),
			_isLocal(true),
			_isOwner(false),
			_name(obj._name),
			_originalName(obj._originalName),
			_started(false),
			_stopped(false),
			_enabled(true),
			_destroyed(false),
			_layer(0)
		{
			for (auto& e : obj._components)
				addComponent(e->clone());
		}

		size_t GameObject::instanceId() const
		{
			return _instanceId;
		}

		void GameObject::name(const std::string& value)
		{
			_name = value;
		}

		const std::string& GameObject::name() const
		{
			return _name;
		}

		void GameObject::instanceId(size_t instanceId)
		{
			_instanceId = instanceId;
		}

		void GameObject::setNetwork(bool local, bool owner)
		{
			_isLocal = local;
			_isOwner = owner;
		}

		bool GameObject::isLocal() const
		{
			return _isLocal;
		}

		bool GameObject::isOwner() const
		{
			return _isOwner;
		}

		void GameObject::loadFile(std::string const & file)
		{
			rtype::ecs::file::Loader loader("assets/entities/" + file + ".json");
			std::vector< std::string > components = loader.getComponents();

			for (std::string const & e : components)
				addComponent(e, loader.getComponent(e));
		}

		void GameObject::addComponent(std::string const& name, file::Value const& values)
		{
			AComponent *component;

			component = _engine.getLibraries().instantiate<AComponent>(name);
			component->setName(name);
			component->loadFile(values);
			addComponent(component);
		}

		void GameObject::addComponent(AComponent *component)
		{
			component->setEngine(&_engine);
			component->setObject(this);
			_components.push_back(std::shared_ptr<AComponent>(component));
		}

		void GameObject::destroy()
		{
			_destroyed = true;
			_engine.flagDelete();
		}

		bool GameObject::mustBeDeleted() const
		{
			return (_destroyed);
		}

		void GameObject::start()
		{
			for (auto& component : _components)
				component->start();
		}

		void GameObject::update()
		{
			if (!_started)
			{
				_started = true;
				start();
			}
			if (_enabled)
			{
				for (auto& component : _components)
					component->update();
			}
		}

		void GameObject::lateUpdate()
		{
			if (_enabled)
			{
				for (auto& component : _components)
					component->lateUpdate();
			}
		}

		void GameObject::onGUI()
		{
			if (_enabled)
			{
				for (auto& component : _components)
					component->onGUI();
			}
		}

		void GameObject::draw()
		{
			if (_enabled)
			{
				for (auto& component : _components)
					component->draw();
			}
		}

		void GameObject::stop()
		{
			if (_enabled && !_stopped)
			{
				_stopped = true;
				for (auto& component : _components)
					component->stop();
			}
		}

		void GameObject::setEnabled(bool enabled)
		{
			_enabled = enabled;
		}

		bool GameObject::enabled() const
		{
			return _enabled;
		}

		void GameObject::layer(int32_t value)
		{
			if (_layer != value)
			{
				_layer = value;
				_engine.flagOrder();
			}
		}

		int32_t GameObject::layer() const
		{
			return _layer;
		}

		void GameObject::serialize(network::types::Entity& entity)
		{
			entity.id(_instanceId);
			entity.name(_name);
			entity.originalName(_originalName);
			entity.owner(_isOwner);
			entity.enabled(_enabled);

			std::ostringstream oss;
			system::BinaryWriter writer(oss);
			for (auto& component : _components)
				component->serialize(writer);
			entity.componentsData(oss.str());
		}

		void GameObject::unserialize(const network::types::Entity& entity)
		{
			_name = entity.name();
			_enabled = entity.enabled();

			if (!entity.owner())
			{
				std::istringstream iss(entity.componentsData());
				system::BinaryReader reader(iss);
				for (auto& component : _components)
					component->unserialize(reader);
				if (static_cast<size_t>(iss.tellg()) != entity.componentsData().size())
					std::cerr << "[warning] " << _name << " did not unserialize properly!"
							  << " expected " << iss.tellg() << " bytes,"
							  << " received " << entity.componentsData().size()
							  << std::endl;
			}
		}
	} // namespace ecs
} // namespace rtype
