#include <iostream>
#include "RType/System/Random.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "BossComponent.hpp"

RTYPE_COMPONENT_IMPL(BossComponent)

void BossComponent::loadFile(rtype::ecs::file::Value const& file)
{
	if (file.hasField("sprite-p1"))
		_spritep1 = file["sprite-p1"].asString();
	else
		_spritep1 = "";

	if (file.hasField("sprite-p2"))
		_spritep2 = file["sprite-p2"].asString();
	else
		_spritep2 = "";
}

void BossComponent::checkDepencies(std::shared_ptr<ITransform> const & t,
	std::shared_ptr<IBehavior> const & b,
	std::shared_ptr<IAnimations> const & a,
	std::shared_ptr<IShootableEnemy> const & s) const
{
	if (!t)
		throw std::runtime_error("cannot use Boss component without Transform component");
	if (!b)
		throw std::runtime_error("cannot use Boss component without Behavior component");
	if (!a)
		throw std::runtime_error("cannot use Boss component without Animations component");
	if (!s)
		throw std::runtime_error("cannot use Boss component without ShootableEnemy component");
	if (!gameObject().getComponent<ICollider>())
		throw std::runtime_error("cannot use Boss component without Collider component");
	if (!gameObject().getComponent<ISpriteRenderer>())
		throw std::runtime_error("cannot use Boss component without SpriteRenderer component");
}

void BossComponent::start()
{
	if (!gameObject().isLocal())
		return ;
	auto t = gameObject().getComponent<ITransform>();
	auto b = gameObject().getComponent<IBehavior>();
	auto a = gameObject().getComponent<IAnimations>();
	auto s = gameObject().getComponent<IShootableEnemy>();
	checkDepencies(t, b, a, s);

	_baseLife = s->life();
	_destroy = false;
	_stade = 1;
	_vScrollingSpeed = rtype::ecs::Vector2f(0.f, 50.f);

	gameObject().name("boss");
	_patternInit = false;
	_patternPlaying = 0;
	_pattern.push_back(std::bind(&BossComponent::startPattern, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_pattern.push_back(std::bind(&BossComponent::laserPattern, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_pattern.push_back(std::bind(&BossComponent::openPattern, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_pattern.push_back(std::bind(&BossComponent::scrollingPattern, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_pattern.push_back(std::bind(&BossComponent::closePattern, this,
			std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void BossComponent::launchMinion(ITransform & t, float y, float speedY)
{
	rtype::ecs::GameObject* obj;
	if (_stade == 1)
		obj = gameEngine().createGameObject("BossMinion");
	else
		obj = gameEngine().createGameObject("BossMinion2");
	auto objT = obj->getComponent<ITransform>();
	auto objB = obj->getComponent<IBehavior>();
	if (!objT)
		throw std::runtime_error("cannot use BossMinon without a Transform component");
	if (!objB)
		throw std::runtime_error("cannot use BossMinon without a Behavior component");
	objT->setPosition(t.getAbsolutePosition() + rtype::ecs::Vector2f(195, y));
	objB->setSpeed(rtype::ecs::Vector2f(-220, speedY));
}

void BossComponent::launchMinions(ITransform & t, IAnimations & a)
{
	// remove blinking by creating the unit just before the end of the animation
	static float cd = a.getAnimationDuration("attack") - a.getSpeed("attack") / 3;

	cd -= gameEngine().getElapsedTime();
	if (cd < 0)
	{
		cd = a.getAnimationDuration("attack");
		launchMinion(t, 84, -20);
		launchMinion(t, 246, 20);
	}
}

bool BossComponent::scrollingPattern(ITransform & t,
	IBehavior & b, IAnimations & a)
{
	if (!_patternInit)
	{
		_patternCd = a.getAnimationDuration("attack") * 20;
		if (_patternCd < gameEngine().getElapsedTime() + 0.0001)
			throw std::runtime_error("Boss cannot have null time animations");
	}

	if (!a.isPlaying("attack"))
		a.setAnim("attack");
	_patternCd -= gameEngine().getElapsedTime();
	if (_patternCd < 0)
		return true;

	auto pos = t.getPosition();

	if (!a.isPlaying("attack"))
		a.setAnim("attack");
	if (pos.y > 500)
		b.setSpeedY(-_vScrollingSpeed.y);
	else if (pos.y < -50)
		b.setSpeedY(_vScrollingSpeed.y);
	else if ((b.getSpeed().y != _vScrollingSpeed.y
			&& b.getSpeed().y != -_vScrollingSpeed.y)
		|| b.getSpeed().x != _vScrollingSpeed.x)
		b.setSpeed(_vScrollingSpeed);
	launchMinions(t, a);
	return false;
}

bool BossComponent::startPattern(ITransform& t,
	IBehavior& b, IAnimations& a)
{
	if (!a.isPlaying("moving"))
		a.setAnim("moving");
	if (b.getSpeed().x != -50)
		b.setSpeedX(-50);
	if (t.getPosition().x > 700)
		return false;
	b.setSpeedX(0);
	return true;
}

bool BossComponent::laserPattern(ITransform& t,
	IBehavior& b, IAnimations& a)
{
	std::shared_ptr<ITransform> laser;
	if (!_patternInit)
	{
		b.setSpeed(rtype::ecs::Vector2f(0.f, 0.f));
		a.setAnim("laser");
		auto obj = gameEngine().createGameObject("BossLaser");
		laser = obj->getComponent<ITransform>();
		laser->setPosition(t.getAbsolutePosition() + rtype::ecs::Vector2f(-860, 179));
		laser->setSize(rtype::ecs::Vector2f(1, 0.05f));
		_patternCd = a.getAnimationDuration("laser");
		if (_patternCd < gameEngine().getElapsedTime() + 0.0001)
			throw std::runtime_error("Boss cannot have null time animations");

	}

	_patternCd -= gameEngine().getElapsedTime();

	if (_patternCd > 0)
		return false;
	a.setAnim("default");
	return true;
}

bool BossComponent::closePattern(ITransform&,
	IBehavior&, IAnimations& a)
{
	if (!_patternInit)
	{
		_patternCd = a.getAnimationDuration("close");
		if (_patternCd < gameEngine().getElapsedTime() + 0.0001)
			throw std::runtime_error("Boss cannot have null time animations");
	}
	_patternCd -= gameEngine().getElapsedTime();
	if (_patternCd < 0)
	{
		return true;
	}

	if (!a.isPlaying("close"))
		a.setAnim("close");
	return false;
}

bool BossComponent::openPattern(ITransform &,
	IBehavior &, IAnimations & a)
{
	if (!_patternInit)
	{
		_patternCd = a.getAnimationDuration("open");
		if (_patternCd < gameEngine().getElapsedTime() + 0.0001)
			throw std::runtime_error("Boss cannot have null time animations");
	}
	_patternCd -= gameEngine().getElapsedTime();
	if (_patternCd < 0)
	{
		return true;
	}

	if (!a.isPlaying("open"))
		a.setAnim("open");
	return false;
}

void BossComponent::explosion(ITransform& t)
{
	static const std::string etype[] =
		{
			"explosions/Small",
			"explosions/Medium",
			"explosions/Large"
		};

	auto obj = gameEngine().createGameObject(etype[rtype::system::random::next(3)]);
	auto objT = obj->getComponent<ITransform>();
	if (!objT)
		throw std::runtime_error("Invalid use of explosion without transform");
	auto const & clist = gameObject().getComponent<ICollider>()->getHitbox();
	if (clist.size() == 0)
		return;
	size_t rand = rtype::system::random::next(clist.size());
	auto it = clist.begin();
	for (size_t i = 0; i < rand && i < clist.size(); i++)
		it++;
	objT->setPosition(t.getPosition() + rtype::ecs::Vector2f((*it).x, (*it).y));
}

bool BossComponent::destroyPattern(ITransform& t,
	IBehavior& b, IAnimations& a)
{
	auto sr = gameObject().getComponent<ISpriteRenderer>();
	auto deltaT = gameEngine().getElapsedTime();
	if (!_patternInit)
	{
		sr->setColor(rtype::ecs::Color(255, 80, 80, 80));
		_explosions = static_cast<size_t>(a.getAnimationDuration("all")) * 5;
		b.setSpeed(rtype::ecs::Vector2f(-30, 30));
		_patternCd = a.getAnimationDuration("all");
		if (_patternCd < gameEngine().getElapsedTime() + 0.0001)
			throw std::runtime_error("Boss cannot have null time animations");
	}
	t.setRotation(t.getRotation() - 3 * deltaT);
	_patternCd -= deltaT;
	if (_patternCd < static_cast<float>(_explosions / 5))
	{
		if (sr->getColor().b > 50)
			sr->setColor(rtype::ecs::Color(sr->getColor().a,
					sr->getColor().r - 2,
					sr->getColor().g - 4,
					sr->getColor().b - 4));
		else if (sr->getColor().a > 1)
			sr->setColor(rtype::ecs::Color(sr->getColor().a - 2,
					sr->getColor().r,
					sr->getColor().g,
					sr->getColor().b));

		explosion(t);
		_explosions--;
	}
	if (_patternCd < 0)
	{
		gameObject().destroy();
		return true;
	}
	if (!a.isPlaying("all"))
		a.setAnim("all");
	return false;
}

void BossComponent::update()
{
	auto a = gameObject().getComponent<IAnimations>();
	if (a && _stade == 2 && _spritep2 != "")
	{
		a->setSprite(_spritep2);
	}
	if (!gameObject().isLocal())
		return ;
	auto t = gameObject().getComponent<ITransform>();
	auto b = gameObject().getComponent<IBehavior>();
	auto s = gameObject().getComponent<IShootableEnemy>();
	auto sr = gameObject().getComponent<ISpriteRenderer>();

	if (_destroy || s->life() <= 0)
	{
		if (!_destroy)
		{
			_destroy = true;
			_patternInit = false;
		}
		destroyPattern(*t, *b, *a);
		_patternInit = true;
		return;
	}
	if (s->life() <= _baseLife / 2 && _stade == 1)
	{
		explosion(*t);
		explosion(*t);
		explosion(*t);
		explosion(*t);
		explosion(*t);

		if (_spritep2 != "")
			a->setSprite(_spritep2);
		_stade = 2;
		_vScrollingSpeed.y *= 3;
	}
	while (_pattern[_patternPlaying](*t, *b, *a))
	{
		_patternInit = false;
		_patternPlaying++;
		if (_patternPlaying >= _pattern.size())
			_patternPlaying = 1;
	}
	_patternInit = true;
}

void BossComponent::serialize(rtype::system::BinaryWriter& writer)
{
	writer << static_cast<uint8_t>(_stade);
}

void BossComponent::unserialize(rtype::system::BinaryReader& reader)
{
	reader >> _stade;
}
