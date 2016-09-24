#ifndef COLLIDERMANAGE_HPP_
# define ColliderSystem_HPP_

# include "IColliderSystem.hpp"
# include "ICollider.hpp"
# include "Components/Transform/ITransform.hpp"
# include "RType/ECS/Rect.hpp"
# include "ICollision.hpp"

RTYPE_PLUGIN
class ColliderSystem : public IColliderSystem, public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

public:
	virtual ~ColliderSystem() {}

private:
	std::list<rtype::ecs::GameObject *> _objects;

public:
	virtual void subscribeCollision(rtype::ecs::GameObject *);
	virtual void unsubscribeCollision(rtype::ecs::GameObject *);
	virtual void update();

private:
	void callCollisions(std::list<rtype::ecs::GameObject *>::iterator &, std::list<rtype::ecs::GameObject *>::iterator &);
	void getCollisionInfos(const rtype::ecs::Rect<float> &, rtype::ecs::Rect<float> &, float &, std::shared_ptr<ITransform> &);
};

#endif
