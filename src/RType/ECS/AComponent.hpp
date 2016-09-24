#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "RType/System/BinaryReader.hpp"
#include "RType/System/BinaryWriter.hpp"
#include "RType/Library/IPlugin.hpp"
#include "RType/ECS/File/Loader.hpp"

#define RTYPE_COMPONENT \
	public: virtual AComponent* clone() const; private:

#define RTYPE_COMPONENT_IMPL(TYPE)										\
	rtype::ecs::AComponent* TYPE::clone() const							\
	{																	\
		return new TYPE(*this);											\
	}																	\
	rtype::library::IPlugin* plugin_instantiate()						\
	{																	\
		return new TYPE;												\
	}

namespace rtype
{
	namespace ecs
	{
		class GameEngine;
		class GameObject;

		class AComponent : public rtype::library::IPlugin
		{
		private:
			std::string _name;
			GameEngine* _gameEngine;
			GameObject* _gameObject;

		public:
			virtual ~AComponent() {}

		public:
			virtual void start() {}
			virtual void update() {}
			virtual void lateUpdate() {}
			virtual void draw() {}
			virtual void onGUI() {}
			virtual void stop() {}

			virtual void loadFile(const file::Value&) {}
			virtual void serialize(system::BinaryWriter&) {}
			virtual void unserialize(system::BinaryReader&) {}

			virtual AComponent* clone() const = 0;

			const std::string& name() const { return _name; }
			GameEngine& gameEngine() const { return *_gameEngine; }
			GameObject& gameObject() const { return *_gameObject; }

			void setName(const std::string& name) { _name = name; }
			void setEngine(GameEngine* engine) { _gameEngine = engine; }
			void setObject(GameObject* object) { _gameObject = object; }
		};
	} // namespace ecs
} // namespace rtype

#endif // !ACOMPONENT_HPP_
