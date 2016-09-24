#include "ColliderSystem.hpp"

RTYPE_COMPONENT_IMPL(ColliderSystem)

void ColliderSystem::subscribeCollision(rtype::ecs::GameObject *obj)
{
	_objects.push_back(obj);
}

void ColliderSystem::unsubscribeCollision(rtype::ecs::GameObject *obj)
{
	_objects.remove(obj);
}

void ColliderSystem::callCollisions(std::list<rtype::ecs::GameObject *>::iterator &it, std::list<rtype::ecs::GameObject *>::iterator &it2)
{
	{
		auto collision = (*it2)->getComponent<ICollision>();
		if (collision)
			collision->onCollision(*(*it));
	}
	{
		auto collision = (*it)->getComponent<ICollision>();
		if (collision)
			collision->onCollision(*(*it2));
	}
}

void ColliderSystem::getCollisionInfos(const rtype::ecs::Rect<float> &e, rtype::ecs::Rect<float> &hitbox, float &z, std::shared_ptr<ITransform> &transform)
{
	rtype::ecs::Vector3<float> position;

	hitbox = e;
	position = transform->getAbsolutePosition();
	z = position.z;
	hitbox += position;
}

void ColliderSystem::update()
{
	if (!gameObject().isLocal()) return;

	std::shared_ptr<ICollider> collider[2];
	std::shared_ptr<ITransform> transform[2];
	rtype::ecs::Rect<float> hitbox[2];
	float z[2];

	if (_objects.size() <= 1)
		return;
	for (auto it = _objects.begin(); it != _objects.end(); ++it)
	{
		auto it2 = it;
		collider[0] = (*it)->getComponent<ICollider>();
		transform[0] = (*it)->getComponent<ITransform>();

		if (it2 != _objects.end())
			++it2;

		for (it2 = it2; it2 != _objects.end(); ++it2)
		{
			collider[1] = (*it2)->getComponent<ICollider>();
			transform[1] = (*it2)->getComponent<ITransform>();

			for (auto const & e : collider[0]->getHitbox())
			{
				getCollisionInfos(e, hitbox[0], z[0], transform[0]);
				for (auto const & e2 : collider[1]->getHitbox())
				{
					getCollisionInfos(e2, hitbox[1], z[1], transform[1]);
					if (hitbox[0].intersect(hitbox[1]) && (std::abs(z[0] - z[1]) <= 0.001))
						callCollisions(it, it2);
				}
			}
		}
	}
}