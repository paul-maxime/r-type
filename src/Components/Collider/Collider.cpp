#include "Collider.hpp"

RTYPE_COMPONENT_IMPL(Collider)

void Collider::loadFile(const rtype::ecs::file::Value& file)
{
	using namespace rtype::ecs;

	Rect<float> hitbox;

	hitbox.x = file.getFloat("x");
	hitbox.y = file.getFloat("y");
	hitbox.width = file.getFloat("width");
	hitbox.height = file.getFloat("height");
	_hitbox.push_back(hitbox);
	if (file.hasField("hitbox"))
	{
		for (size_t i = 0; i < file["hitbox"].size(); i++)
		{
			auto const & v = file["hitbox"][i];

			hitbox = Rect<float>(v[0].asFloat(), v[1].asFloat(),
				v[2].asFloat(), v[3].asFloat());
			_hitbox.push_back(hitbox);
		}
	}
	if (file.hasField("debug"))
		_debug = file["debug"].asBool();
	else
		_debug = false;
}

const std::list<rtype::ecs::Rect<float>>& Collider::getHitbox() const
{
	if (_hitbox.size() > 1)
	{
		_hitbox.size();
	}
	return _hitbox;
}

void Collider::start()
{
	rtype::ecs::GameObject *obj = gameEngine().find("ColliderSystem");

	if (obj)
	{
		_manager = obj->getComponent<IColliderSystem>();
		if (auto manager = _manager.lock())
			manager->subscribeCollision(&gameObject());
	}
}

void Collider::stop()
{
	if (auto manager = _manager.lock())
		manager->unsubscribeCollision(&gameObject());
}

void Collider::draw()
{
	using namespace rtype::ecs;

	if (_debug)
	{
		auto t = gameObject().getComponent<ITransform>();

		if (t)
		{
			for (auto const & hitbox : _hitbox)
			{
				gameEngine().getGraphics().draw("sprites/hitbox.png",
					t->getAbsolutePosition() + Vector2f(hitbox.x, hitbox.y),
					IntRect(static_cast<int>(hitbox.x),
					static_cast<int>(hitbox.y),
					static_cast<int>(hitbox.width),
					static_cast<int>(hitbox.height)),
					Vector2f(1.f, 1.f), Color(150, 255, 255, 255));
			}
		}
	}
}
