#ifndef SCENECOMPONENT_HPP_
#define SCENECOMPONENT_HPP_

#include <vector>

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class SceneComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::vector<std::string> _objects;

public:
	virtual ~SceneComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
};

#endif // !SCENECOMPONENT_HPP_
