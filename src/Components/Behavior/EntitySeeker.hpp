#ifndef ENTITY_SEEKER_HPP_
#define ENTITY_SEEKER_HPP_

#include "RType/ECS/GameObject.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/ColliderSystem/ICollider.hpp"

class EntitySeeker
{
public:
	~EntitySeeker() {}

	template<typename T>
	static bool seekPosition(const rtype::ecs::GameObject& obj,
							 const rtype::ecs::GameEngine& engine,
							 rtype::ecs::Vector3f& pos,
							 const rtype::ecs::Vector3f& offset = rtype::ecs::Vector3f(0, 0, 0),
							 bool useCollider = true)
	{
		bool set = false;
		auto gameObjects = engine.gameObjects();
		auto self = obj.getComponent<ITransform>();
		if (!self)
			return (false);
		rtype::ecs::Vector3f mpos = self->getAbsolutePosition() + offset;

		auto sCollider = obj.getComponent<ICollider>();
		if (sCollider && useCollider)
		{
			auto sHitboxes = sCollider->getHitbox();
			if (sHitboxes.size())
				mpos += rtype::ecs::Vector3f(sHitboxes.front().x + sHitboxes.front().width / 2,
											 sHitboxes.front().y + sHitboxes.front().height / 2, 0);
		}

		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			if ((*it)->getComponent<T>())
			{
				auto t = (*it)->getComponent<ITransform>();
				auto collider = (*it)->getComponent<ICollider>();

				if (t && collider)
				{
					auto hitboxes = collider->getHitbox();
					const rtype::ecs::Vector3f& epos = t->getAbsolutePosition();
					for (auto ith = hitboxes.begin(); ith != hitboxes.end(); ++ith)
					{
						rtype::ecs::Vector3f center(ith->x + ith->width / 2, ith->y + ith->height / 2, 0);
						rtype::ecs::Vector3f tmp = epos + center;
						if (!set)
						{
							pos = tmp;
							set = true;
						}
						else if (mpos.distance(pos) > mpos.distance(tmp))
						{
							pos = tmp;
						}
					}
				}
			}
		}
		return (set);
	};

	template<typename T>
	static bool seekAngle(const rtype::ecs::GameObject& obj,
						  const rtype::ecs::GameEngine& engine,
						  float& angle,
						  const rtype::ecs::Vector3f& offset = rtype::ecs::Vector3f(0, 0, 0),
						  bool useCollider = true)
	{
		rtype::ecs::Vector3f pos;
		if (!seekPosition<T>(obj, engine, pos, offset, useCollider))
			return (false);
		auto self = obj.getComponent<ITransform>();
		rtype::ecs::Vector3f mpos = self->getAbsolutePosition() + offset;

		auto sCollider = obj.getComponent<ICollider>();
		if (sCollider && useCollider)
		{
			auto sHitboxes = sCollider->getHitbox();
			if (sHitboxes.size())
				mpos += rtype::ecs::Vector3f(sHitboxes.front().x + sHitboxes.front().width / 2,
											 sHitboxes.front().y + sHitboxes.front().height / 2, 0);
		}

		float x = std::abs(mpos.x - pos.x);
		float y = std::abs(mpos.y - pos.y);
		if (x == 0)
		{
			if (pos.y > mpos.y)
				angle = 270;
			else
				angle = 90;
		}
		else
		{
			angle = std::atan(y / x) * 180.f / 3.14159265359f;
			if (pos.x < mpos.x)
				angle = (pos.y > mpos.y ? angle + 180 : 90 - angle + 90);
			else if (pos.y > mpos.y)
				angle = 90 - angle + 270;
		}
		angle = fmodf(angle, 360);
		if (angle < 0)
			angle = 360 + angle;
		return (true);
	};
};

#endif /* !ENTITY_SEEKER_HPP_ */
