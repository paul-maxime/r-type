#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "Components/DestroyEvent/IDestroyEvent.hpp"
#include "Components/Transform/ITransform.hpp"
#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class Transform : public rtype::ecs::AComponent, public ITransform
{
	RTYPE_COMPONENT

public:
	virtual ~Transform() {}

private:
	rtype::ecs::Vector3f _pos;
	float _rotation;
	rtype::ecs::Vector2f _origin;

	rtype::ecs::Vector2f _size;
	std::weak_ptr<ITransform> _parent;
	std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>> _onParentDestroy;

public:
	virtual void loadFile(rtype::ecs::file::Value const&);

	virtual void serialize(rtype::system::BinaryWriter&);
	virtual void unserialize(rtype::system::BinaryReader&);

	virtual float getZ() const;

	virtual void setPosition(float, float, float = 0);
	virtual void move(float, float);

	virtual void setPosition(const rtype::ecs::Vector2f &);
	virtual void move(const rtype::ecs::Vector2f &);

	virtual void setPosition(const rtype::ecs::Vector3f &);
	virtual void move(const rtype::ecs::Vector3f &);

	virtual const rtype::ecs::Vector3f &getPosition() const;
	virtual const rtype::ecs::Vector3f getAbsolutePosition() const;

	virtual const rtype::ecs::Vector2f &getSize() const;
	virtual void setSize(rtype::ecs::Vector2f const & v);

	virtual void setRotation(float rotation);
	virtual float getRotation() const;
	virtual void rotate(float delta);

	virtual void setOrigin(const rtype::ecs::Vector2f& origin);
	virtual const rtype::ecs::Vector2f& getOrigin();

	virtual bool hasParent() const;
	virtual std::shared_ptr<ITransform> parent();
	virtual std::shared_ptr<ITransform> const parent() const;
	virtual void parent(std::shared_ptr<ITransform> obj);
	virtual void parent(rtype::ecs::GameObject& obj);
	virtual void setParent(std::shared_ptr<ITransform> obj);
	virtual void setParent(rtype::ecs::GameObject& obj);
	virtual void unsetParent();
	virtual rtype::ecs::GameObject& parentGameObject();
	virtual rtype::ecs::GameObject const & parentGameObject() const;
	virtual void onParentDestroy(rtype::ecs::GameObject& sender);
};

#endif // !TRANSFORM_HPP_
