#include "RType/ECS/GameEngine.hpp"
#include "DestroyEventComponent.hpp"

RTYPE_COMPONENT_IMPL(DestroyEventComponent)

void DestroyEventComponent::stop()
{
	for (auto& callback : _callbacks)
	{
		auto fct = callback.lock();
		if (fct)
		{
			(*fct)(gameObject());
		}
	}
}

void DestroyEventComponent::subscribe(std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>> fct)
{
	_callbacks.push_back(std::weak_ptr<std::function<void (rtype::ecs::GameObject&)>>(fct));
}
