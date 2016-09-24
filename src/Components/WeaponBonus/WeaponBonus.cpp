#include "Components/PlayerShip/IPlayerShip.hpp"
#include "WeaponBonus.hpp"

RTYPE_COMPONENT_IMPL(WeaponBonus)

#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "Components/Weapons/WeaponsHolder/IWeaponsHolder.hpp"

void WeaponBonus::onCollision(rtype::ecs::GameObject &collision)
{
	if (collision.getComponent<IPlayerShip>())
	{
		std::shared_ptr<IWeaponsHolder> ptr = collision.getComponent<IWeaponsHolder>();

		if (ptr)
		{
			ptr->upgrade();
			gameObject().destroy();
		}
	}
}
