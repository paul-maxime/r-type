#include <cmath>

#include "Transform.hpp"

RTYPE_COMPONENT_IMPL(Transform)

void Transform::loadFile(rtype::ecs::file::Value const& file)
{
	if (file.hasField("position"))
	{
		auto const & position = file["position"];
		_pos.x = position[0].asFloat();
		if (position.size() >= 2)
			_pos.y = position[1].asFloat();
		if (position.size() >= 3)
			_pos.z = position[2].asFloat();
	}

	_rotation = file.getFloat("rotation");

	if (file.hasField("origin"))
	{
		auto const & origin = file["origin"];
		_origin.x = origin[0].asFloat();
		_origin.y = origin[1].asFloat();
	}

	if (file.hasField("size"))
	{
		auto const & size = file["size"];
		_size.x = size[0].asFloat();
		_size.y = size[1].asFloat();
	}
	else
		_size = rtype::ecs::Vector2f(1.0f, 1.0f);
}

void Transform::serialize(rtype::system::BinaryWriter& writer)
{
	auto const & v = getAbsolutePosition();
	writer << static_cast<int16_t>(v.x)
		   << static_cast<int16_t>(v.y)
		   << static_cast<int16_t>(v.z)
		   << static_cast<int16_t>(_rotation)
		   << static_cast<uint16_t>(_size.x * 1000.0f)
		   << static_cast<uint16_t>(_size.y * 1000.0f);
}

void Transform::unserialize(rtype::system::BinaryReader& reader)
{
	int16_t x, y, z, rotation;
	uint16_t sizeX, sizeY;

	reader >> x >> y >> z >> rotation >> sizeX >> sizeY;
	_pos.x = static_cast<float>(x);
	_pos.y = static_cast<float>(y);
	_pos.z = static_cast<float>(z);
	_rotation = static_cast<float>(rotation);
	_size.x = static_cast<float>(sizeX) / 1000.0f;
	_size.y = static_cast<float>(sizeY) / 1000.0f;
}

float Transform::getZ() const
{
	return (_pos.z);
}

void Transform::setPosition(float x, float y, float z)
{
	setPosition(rtype::ecs::Vector3f(x, y, z));
}

void Transform::move(float x, float y)
{
	_pos.x += x;
	_pos.y += y;
}

void Transform::setPosition(const rtype::ecs::Vector2f &v)
{
	_pos.x = v.x;
	_pos.y = v.y;
}

void Transform::move(const rtype::ecs::Vector2f &v)
{
	_pos.x += v.x;
	_pos.y += v.y;
}

void Transform::setPosition(const rtype::ecs::Vector3f &v)
{
	_pos = v;
	if (std::abs(v.z - _pos.z) > 0.001)
	{
		int layer = static_cast<int>(v.z * -1);
		if (layer <= -1000)
			layer = -999;
		else if (layer >= 1000)
			layer = 999;
		gameObject().layer(layer);
	}
}

void Transform::move(const rtype::ecs::Vector3f &v)
{
	_pos = _pos + v;
}

const rtype::ecs::Vector3f &Transform::getPosition() const
{
	return (_pos);
}

const rtype::ecs::Vector3f Transform::getAbsolutePosition() const
{
	rtype::ecs::Vector3f ret = _pos;

	auto ptr = _parent.lock();
	if (ptr)
	{
		ret += ptr->getAbsolutePosition();
	}
	return (ret);
}

const rtype::ecs::Vector2f &Transform::getSize() const
{
	return (_size);
}

void Transform::setSize(rtype::ecs::Vector2f const & v)
{
	_size = v;
}

void Transform::setRotation(float rotation)
{
	_rotation = rotation;
}

float Transform::getRotation() const
{
	return _rotation;
}

void Transform::rotate(float delta)
{
	_rotation += delta;
	_rotation = fmodf(_rotation, 360.0f);
}

void Transform::setOrigin(const rtype::ecs::Vector2f& origin)
{
	_origin = origin;
}

const rtype::ecs::Vector2f& Transform::getOrigin()
{
	return _origin;
}

bool Transform::hasParent() const
{
	if (_parent.lock())
		return true;
	return false;
}

std::shared_ptr<ITransform> Transform::parent()
{
	return _parent.lock();
}

std::shared_ptr<ITransform> const Transform::parent() const
{
	return _parent.lock();
}

void Transform::parent(std::shared_ptr<ITransform> objT)
{
	if (!objT)
		throw std::logic_error("cannot set the GameObject parent to a non existing GameObject");
	if (this == objT.get())
		throw std::logic_error("cannot set a Transform parent to itself");
	_parent = objT;

	auto & obj = std::dynamic_pointer_cast<AComponent>(objT)->gameObject();

	auto event = obj.getComponent<IDestroyEvent>();
	if (!event)
		throw std::runtime_error("cannot set a Transform parent without DestroyEvent");
	_onParentDestroy = std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>>
		(new std::function<void (rtype::ecs::GameObject&)>
			(std::bind(&Transform::onParentDestroy, this, std::placeholders::_1)));
	event->subscribe(_onParentDestroy);
}

void Transform::setParent(std::shared_ptr<ITransform> objT)
{
	parent(objT);
}

void Transform::parent(rtype::ecs::GameObject& obj)
{
	if (!obj.getComponent<ITransform>())
	{
		throw std::runtime_error("cannot set an object with no Transform as a parent");
	}
	parent(obj.getComponent<ITransform>());
}

void Transform::setParent(rtype::ecs::GameObject& obj)
{
	parent(obj);
}

void Transform::unsetParent()
{
	_parent = std::shared_ptr<ITransform>();
}

rtype::ecs::GameObject& Transform::parentGameObject()
{
	auto ptr= _parent.lock();
	if (!ptr)
		throw std::runtime_error("cannot get the GameObject of a non existing parent");
	return std::dynamic_pointer_cast<AComponent>(ptr)->gameObject();
}

rtype::ecs::GameObject const & Transform::parentGameObject() const
{
	auto ptr= _parent.lock();
	if (!ptr)
		throw std::runtime_error("cannot get the GameObject of a non existing parent");
	return std::dynamic_pointer_cast<AComponent>(ptr)->gameObject();
}

void Transform::onParentDestroy(rtype::ecs::GameObject& sender)
{
	auto senderT = sender.getComponent<ITransform>();
	if (senderT)
		_pos += senderT->getAbsolutePosition();
}
