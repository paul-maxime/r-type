#include "Components/PlayerShip/IPlayerShip.hpp"
#include "SpeedBonus.hpp"

RTYPE_COMPONENT_IMPL(SpeedBonus)

#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "RType/ECS/GameEngine.hpp"

void SpeedBonus::loadFile(const rtype::ecs::file::Value& file)
{
	_givenSpeed = file.getFloat("speed", 300.f);
}

void SpeedBonus::onCollision(rtype::ecs::GameObject &collision)
{
	if (collision.getComponent<IPlayerShip>())
	{
		collision.getComponent<APlayerControllable>()->getPlayer()->addSpeed(_givenSpeed);
		gameObject().destroy();
	}
}
