#include <iostream>

#include "RType/ECS/GameEngine.hpp"
#include "LayerComponent.hpp"

RTYPE_COMPONENT_IMPL(LayerComponent)

void LayerComponent::loadFile(const rtype::ecs::file::Value& file)
{
	if (file.isNumeric())
		_layer = file.asInt();
	else
	{
		std::cerr << "[warning] a layer component is invalid" << std::endl;
		_layer = 0;
	}
}

void LayerComponent::start()
{
	gameObject().layer(_layer);
}
