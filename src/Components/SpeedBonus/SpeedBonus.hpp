#ifndef SPEEDBONUS_HPP_
# define SPEEDBONUS_HPP_

# include "RType/ECS/AComponent.hpp"
# include "Components/Player/IPlayerComponent.hpp"
# include "Components/ColliderSystem/ICollision.hpp"

RTYPE_PLUGIN
class SpeedBonus : public rtype::ecs::AComponent, public ICollision
{
	RTYPE_COMPONENT

private:
	float _givenSpeed;

public:
	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void onCollision(rtype::ecs::GameObject &);

};

#endif
