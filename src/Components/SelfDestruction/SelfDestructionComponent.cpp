#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/ColliderSystem/ICollider.hpp"
#include "SelfDestructionComponent.hpp"

RTYPE_COMPONENT_IMPL(SelfDestructionComponent)

void SelfDestructionComponent::update()
{
	if (!gameObject().isLocal()) return;

	auto transform = gameObject().getComponent<ITransform>();
	if (transform)
	{
		rtype::ecs::Vector3f pos = transform->getAbsolutePosition();
		rtype::ecs::Rect<float> hitbox(0.0f, 0.0f, 64.0f, 64.0f);
		auto collider = gameObject().getComponent<ICollider>();
		if (collider)
		{
			hitbox.width += collider->getHitbox().front().width;
			hitbox.height += collider->getHitbox().front().height;
		}
		else
		{
			hitbox.width += 128.0f;
			hitbox.height += 128.0f;
		}
		if (pos.x < -hitbox.width || pos.y < -hitbox.height ||
			pos.x > 1024.0f + hitbox.width || pos.y > 768.0f + hitbox.height)
		{
			gameObject().destroy();
		}
	}
}
