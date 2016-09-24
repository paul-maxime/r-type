#include <iostream>

#include "GameEngine.hpp"
#include "Rect.hpp"

namespace rtype
{
	namespace ecs
	{
		GameEngine::GameEngine(std::shared_ptr<IGraphicsEngine> graphics,
			std::shared_ptr<IAudioEngine> audio,
			std::shared_ptr<IInput> inputs,
			std::shared_ptr<INetworkEngine> network)
			: _actualId(0), _running(true), _mustDelete(false), _mustOrder(false),
			  _graphics(graphics), _audio(audio), _inputs(inputs), _network(network),
			  _clock(std::chrono::steady_clock::now())
		{
		}

		GameEngine::~GameEngine()
		{
			for (auto & obj : _gameObjects)
			{
				obj.reset();
			}
			for (auto & obj : _newGameObjects)
			{
				obj.reset();
			}
			for (auto& pair : _entityModels)
			{
				pair.second.reset();
			}
		}

		float GameEngine::getElapsedTime()
		{
			return (_elapsedTime);
		}

		void GameEngine::orderGameObjectsByLayer()
		{
			_gameObjects.sort([] (std::shared_ptr< GameObject > first,
					std::shared_ptr< GameObject > second) -> bool
				{
					return (first->layer() < second->layer());
				});
			_mustOrder = false;
		}

		void GameEngine::loop()
		{
			while (_running)
				tick();
		}

		void GameEngine::tick()
		{
			using namespace std::chrono;

			milliseconds ms = duration_cast<milliseconds>(steady_clock::now() - _clock);
			_elapsedTime = static_cast<float>(ms.count() / 1000.0f);
			_clock = steady_clock::now();

			if (_elapsedTime > 160.0f)
				_elapsedTime = 160.0f;

			loadNextScene();
			if (_mustOrder)
				orderGameObjectsByLayer();
			update();
			lateUpdate();
			draw();
			createNewObjects();
			if (_mustDelete)
				destroyGameObjects();
		}

		void GameEngine::stopEngine()
		{
			_running = false;
		}

		GameObject *GameEngine::createGameObject(const std::string& name)
		{
			std::shared_ptr< GameObject > obj;

			uint32_t id = ++_actualId;

			obj = createObject(id, name);
			obj->setNetwork(true, false);
			_mustOrder = true;

			return (obj.get());
		}

		GameObject *GameEngine::createRemoteGameObject(const std::string & name,
			bool owner,
			uint32_t id)
		{
			std::shared_ptr< GameObject > obj;

			obj = createObject(id, name);
			obj->setNetwork(false, owner);
			_remoteObjectIds[obj->instanceId()] = obj.get();
			_mustOrder = true;

			return (obj.get());
		}

		GameObject *GameEngine::find(const std::string &str)
		{
			for (auto & gameObject : _gameObjects)
			{
				if (gameObject->name() == str)
					return (gameObject.get());
			}
			for (auto & gameObject : _newGameObjects)
			{
				if (gameObject->name() == str)
					return (gameObject.get());
			}
			return nullptr;
		}

		const std::list<std::shared_ptr< GameObject > >& GameEngine::gameObjects() const
		{
			return _gameObjects;
		}

		GameObject* GameEngine::getRemoteGameObject(uint32_t instanceId)
		{
			auto it = _remoteObjectIds.find(instanceId);
			if (it == _remoteObjectIds.end())
				return nullptr;
			return it->second;
		}

		void GameEngine::flagOrder()
		{
			_mustOrder = true;
		}

		void GameEngine::flagDelete()
		{
			_mustDelete = true;
		}

		void GameEngine::update()
		{
			for (auto & gameObject : _gameObjects)
				gameObject->update();
		}

		void GameEngine::lateUpdate()
		{
			for (auto & gameObject : _gameObjects)
				gameObject->lateUpdate();
		}

		void GameEngine::draw()
		{
			if (!_graphics)
				return;
			_graphics->clear();
			for (auto & gameObject : _gameObjects)
				gameObject->draw();
			for (auto & gameObject : _gameObjects)
				gameObject->onGUI();
			_graphics->display();
		}

		void GameEngine::loadScene(const std::string& name)
		{
			_nextScene = name;
		}

		IGraphicsEngine& GameEngine::getGraphics()
		{
			if (!_graphics)
				throw std::logic_error("graphics is null and should not be get");
			return *_graphics;
		}

		IAudioEngine& GameEngine::getAudio()
		{
			if (!_audio)
				throw std::logic_error("audio is null and should not be get");
			return *_audio;
		}

		IInput& GameEngine::getInputs()
		{
			if (!_inputs)
				throw std::logic_error("inputs is null and should not be get");
			return (*_inputs);
		}

		INetworkEngine& GameEngine::getNetwork()
		{
			if (!_network)
				throw std::logic_error("network is null and should not be get");
			return (*_network);
		}

		library::LibraryManager& GameEngine::getLibraries()
		{
			return _libraries;
		}

		bool GameEngine::hasGraphics()
		{
			return !!_graphics;
		}

		std::shared_ptr<GameObject> GameEngine::createObject(uint32_t id, const std::string& name)
		{
			std::shared_ptr< GameObject > obj;

			if (_entityModels.find(name) != _entityModels.end())
			{
				obj = std::make_shared<GameObject>(*_entityModels[name]);
				obj->instanceId(id);
			}
			else
			{
				obj = std::make_shared<GameObject>(id, *this, name);
				obj->loadFile(name);
				_entityModels[name] = std::unique_ptr<GameObject const>(new GameObject(*(obj.get())));
			}
			_newGameObjects.push_back(std::shared_ptr<GameObject>(obj));

			return obj;
		}

		void GameEngine::loadNextScene()
		{
			if (!_nextScene.empty())
			{
				clearGameObjects();
				createGameObject(_nextScene);
				_nextScene = "";
			}
		}

		void GameEngine::clearScene()
		{
			clearGameObjects();
			_nextScene = "";
		}

		void GameEngine::createNewObjects()
		{
			while (_newGameObjects.size() > 0)
			{
				_gameObjects.push_back(_newGameObjects.front());
				_newGameObjects.pop_front();
				_mustOrder = true;
			}
		}

		void GameEngine::destroyGameObjects()
		{
			while (_mustDelete)
			{
				_mustDelete = false;
				for (auto it = _gameObjects.begin(); it != _gameObjects.end(); ++it)
				{
					const auto& obj = *it;
					if (obj->mustBeDeleted())
						obj->stop();
				}
			}
			for (auto it = _gameObjects.begin(); it != _gameObjects.end();)
			{
				const auto& obj = *it;
				if (obj->mustBeDeleted())
				{
					if (!obj->isLocal())
						_remoteObjectIds.erase(obj->instanceId());

					it = _gameObjects.erase(it);
				}
				else
					++it;
			}
		}

		void GameEngine::clearGameObjects()
		{
			for (auto & obj : _gameObjects)
			{
				obj.reset();
			}
			for (auto & obj : _newGameObjects)
			{
				obj.reset();
			}
			_remoteObjectIds.clear();
			_gameObjects.clear();
			_newGameObjects.clear();
		}

		std::list<std::shared_ptr<GameObject> > &GameEngine::gameObjects()
		{
			return (_gameObjects);
		}
	} // namespace ecs
} // namespace rtype
