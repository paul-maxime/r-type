#include "Components/PlayerShip/IPlayerShip.hpp"
#include "HealBonus.hpp"
#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "RType/ECS/GameEngine.hpp"

RTYPE_COMPONENT_IMPL(HealBonus)


void HealBonus::onCollision(rtype::ecs::GameObject &collision)
{
	if (collision.getComponent<APlayerControllable>())
	{
		collision.getComponent<APlayerControllable>()->getPlayer()->addLife();
		gameObject().destroy();
	}
}
