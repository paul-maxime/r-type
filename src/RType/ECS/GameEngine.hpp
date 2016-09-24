#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include <chrono>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <memory>

#include "RType/ECS/GameObject.hpp"
#include "RType/ECS/IGraphicsEngine.hpp"
#include "RType/ECS/IAudioEngine.hpp"
#include "RType/ECS/INetworkEngine.hpp"
#include "RType/ECS/IInput.hpp"
#include "RType/Library/LibraryManager.hpp"

namespace rtype
{
	namespace ecs
	{
		class GameEngine
		{
		public:
			GameEngine(std::shared_ptr<IGraphicsEngine> graphics = nullptr,
				std::shared_ptr<IAudioEngine> audio = nullptr,
				std::shared_ptr<IInput> inputs = nullptr,
				std::shared_ptr<INetworkEngine> network = nullptr);
			~GameEngine();

		private:
			uint32_t _actualId;
			std::list<std::shared_ptr<GameObject>> _gameObjects;
			std::list<std::shared_ptr<GameObject>> _newGameObjects;
			std::unordered_map<uint32_t, GameObject*> _remoteObjectIds;
			std::unordered_map<std::string, std::unique_ptr<GameObject const>> _entityModels;
			bool _running;
			bool _mustDelete;
			bool _mustOrder;
			float _elapsedTime;
			std::string _nextScene;

			std::shared_ptr<IGraphicsEngine> _graphics;
			std::shared_ptr<IAudioEngine> _audio;
			std::shared_ptr<IInput> _inputs;
			std::shared_ptr<INetworkEngine> _network;
			library::LibraryManager _libraries;

			std::chrono::steady_clock::time_point _clock;

		public:
			float getElapsedTime();

			void orderGameObjectsByLayer();
			void loop();
			void tick();
			void stopEngine();

			GameObject *createGameObject(const std::string& name);

			GameObject *createRemoteGameObject(const std::string& name,
				bool owner,
				uint32_t id);

			GameObject *find(const std::string &);

			const std::list<std::shared_ptr< GameObject > >& gameObjects() const;
			GameObject* getRemoteGameObject(uint32_t instanceId);

			void flagOrder();
			void flagDelete();

			void update();
			void lateUpdate();
			void draw();

			void loadScene(const std::string& name);
			void clearScene();

			IGraphicsEngine& getGraphics();
			IAudioEngine& getAudio();
			IInput& getInputs();
			INetworkEngine& getNetwork();
			library::LibraryManager& getLibraries();

			bool hasGraphics();

			std::list<std::shared_ptr<GameObject> > &gameObjects();

		private:
			std::shared_ptr<GameObject> createObject(uint32_t id, const std::string& name);
			void loadNextScene();
			void createNewObjects();
			void destroyGameObjects();
			void clearGameObjects();
		};
	} // namespace ecs
} // namespace rtype

#endif
