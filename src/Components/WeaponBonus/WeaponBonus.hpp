#ifndef WEAPONBONUS_HPP_
# define WEAPONBONUS_HPP_

# include "RType/ECS/AComponent.hpp"
# include "Components/Player/IPlayerComponent.hpp"
# include "Components/ColliderSystem/ICollision.hpp"

RTYPE_PLUGIN
class WeaponBonus : public rtype::ecs::AComponent, public ICollision
{
	RTYPE_COMPONENT

public:
	virtual void onCollision(rtype::ecs::GameObject &);

};

#endif
