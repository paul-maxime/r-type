#ifndef LAYERCOMPONENT_HPP_
#define LAYERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class LayerComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	int32_t _layer;

public:
	virtual ~LayerComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
};

#endif // !LAYERCOMPONENT_HPP_
