#ifndef ACOLLIDER_HPP_
#define ACOLLIDER_HPP_

#include <list>
#include "RType/ECS/AComponent.hpp"
#include "RType/ECS/Rect.hpp"
#include "Components/ColliderSystem/IColliderSystem.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "Components/ColliderSystem/ICollider.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/Shader/IShader.hpp"

RTYPE_PLUGIN
class Collider : public rtype::ecs::AComponent, public ICollider
{
	RTYPE_COMPONENT

protected:
	std::list<rtype::ecs::Rect<float>> _hitbox;
	std::weak_ptr<IColliderSystem> _manager;
	bool _debug;

public:
	virtual ~Collider() {}
	virtual void loadFile(const rtype::ecs::file::Value& file);
	virtual void draw();
	virtual const std::list<rtype::ecs::Rect<float>>& getHitbox() const;

	virtual void start();
	virtual void stop();
};

#endif // ACOLLIDER_HPP_
