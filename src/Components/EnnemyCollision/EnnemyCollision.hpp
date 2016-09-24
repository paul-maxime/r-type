#ifndef ENNEMYCOLLISION_HPP_
# define ENNEMYCOLLISION_HPP_

# include "Components/ColliderSystem/ICollision.hpp"
# include "RType/ECS/AComponent.hpp"
# include "RType/ECS/GameObject.hpp"

RTYPE_PLUGIN
class EnnemyCollision : public ICollision, public rtype::ecs::AComponent
{
	RTYPE_COMPONENT
public:
	virtual ~EnnemyCollision();

public:
	virtual void onCollision(rtype::ecs::GameObject &);
};

#endif