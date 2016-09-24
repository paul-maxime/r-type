#ifndef BULLET_SPAWNER_HPP_
#define BULLET_SPAWNER_HPP_

#include <string>
#include "RType/ECS/GameEngine.hpp"
#include "RType/ECS/GameObject.hpp"
#include "RType/ECS/Vector2.hpp"
#include "RType/ECS/Vector3.hpp"

class BulletSpawner
{
public:
	virtual ~BulletSpawner() {};

	virtual rtype::ecs::GameObject* createBullet(
		rtype::ecs::GameEngine&, rtype::ecs::GameObject&, const std::string& bullet, float speed = 0,
		float angle = 0, int8_t damage = 0, float rotate = false,
		const rtype::ecs::Vector2f& offset = rtype::ecs::Vector2f(0, 0));

private:
	void move(rtype::ecs::GameObject& obj, rtype::ecs::GameObject& bullet,
			  const rtype::ecs::Vector2f& offset);
	void setSpeed(rtype::ecs::GameObject& bullet, float speed, float angle, float rotate);
};

#endif /* !BULLET_SPAWNER_HPP_ */
