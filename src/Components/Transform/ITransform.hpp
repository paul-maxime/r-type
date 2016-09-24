#ifndef ITRANSFORM_HPP_
#define ITRANSFORM_HPP_

#include "RType/ECS/GameObject.hpp"
#include "RType/ECS/Vector3.hpp"
#include "RType/ECS/GameObject.hpp"

class ITransform
{
public:
	virtual ~ITransform() {}

	virtual float getZ() const = 0;
	virtual void setPosition(float, float, float) = 0;
	virtual void move(float, float) = 0;

	virtual void setPosition(const rtype::ecs::Vector2f &) = 0;
	virtual void move(const rtype::ecs::Vector2f &) = 0;

	virtual void setPosition(const rtype::ecs::Vector3f &) = 0;
	virtual void move(const rtype::ecs::Vector3f &) = 0;

	virtual const rtype::ecs::Vector3f& getPosition() const = 0;
	virtual const rtype::ecs::Vector3f getAbsolutePosition() const = 0;

	virtual const rtype::ecs::Vector2f &getSize() const = 0;
	virtual void setSize(rtype::ecs::Vector2f const & v) = 0;

	virtual void setRotation(float rotation) = 0;
	virtual float getRotation() const = 0;
	virtual void rotate(float delta) = 0;

	virtual void setOrigin(const rtype::ecs::Vector2f& origin) = 0;
	virtual const rtype::ecs::Vector2f& getOrigin() = 0;

	virtual bool hasParent() const = 0;
	virtual std::shared_ptr<ITransform> parent() = 0;
	virtual std::shared_ptr<ITransform> const parent() const = 0;
	virtual void parent(std::shared_ptr<ITransform> obj) = 0;
	virtual void parent(rtype::ecs::GameObject& obj) = 0;
	virtual void setParent(std::shared_ptr<ITransform> obj) = 0;
	virtual void setParent(rtype::ecs::GameObject& obj) = 0;
	virtual void unsetParent() = 0;
	virtual rtype::ecs::GameObject& parentGameObject() = 0;
	virtual rtype::ecs::GameObject const & parentGameObject() const = 0;
	virtual void onParentDestroy(rtype::ecs::GameObject& sender) = 0;
};

#endif // !ITRANSFORM_HPP_
