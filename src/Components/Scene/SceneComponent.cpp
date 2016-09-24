#include "RType/ECS/GameEngine.hpp"
#include "SceneComponent.hpp"

RTYPE_COMPONENT_IMPL(SceneComponent)

void SceneComponent::loadFile(const rtype::ecs::file::Value& file)
{
	for (size_t i = 0; i < file.size(); ++i)
		_objects.push_back(file[i].asString());
}

void SceneComponent::start()
{
	if (!gameObject().isLocal()) return;

	for (const std::string& object : _objects)
		gameEngine().createGameObject(object);
}
