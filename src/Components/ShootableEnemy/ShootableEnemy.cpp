#include "RType/ECS/GameEngine.hpp"
#include "Components/PlayerShip/IPlayerShip.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/Score/IScore.hpp"
#include "ShootableEnemy.hpp"

RTYPE_COMPONENT_IMPL(ShootableEnemy)

void ShootableEnemy::loadFile(const rtype::ecs::file::Value& file)
{
	_life = file.getInt("life", 1);
	_team = file.getInt("team");
	_damage = file.getInt("damage");

	_score = file.getInt("score", 0);

	if (file.hasField("destroy"))
		_manageDestruction = file.getBool("destroy");
	else
		_manageDestruction = true;

	if (file.hasField("hitColor"))
	{
		rtype::ecs::file::Value color = file["color"];
		uint8_t a = color.getInt("a", 255);
		uint8_t r = color.getInt("r", 255);
		uint8_t g = color.getInt("g", 255);
		uint8_t b = color.getInt("b", 255);
		_hitColor = rtype::ecs::Color(a, r, g, b);
	}
	else
		_hitColor = rtype::ecs::Color(255, 255, 110, 110);

	_hitDuration = file.getFloat("hitDuration", 0.10f);

	_colorDelay = 0;
}

void ShootableEnemy::start()
{
	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	if (renderer)
	{
		// _defaultColor = renderer->getColor();
		_defaultColor = rtype::ecs::Color(255, 255, 255, 255);
	}
}

void ShootableEnemy::update()
{
	if (_colorDelay > 0)
	{
		_colorDelay -= gameEngine().getElapsedTime();
		if (_colorDelay <= 0)
		{
			setColor(_defaultColor, 0.0f);
		}
	}
}

void ShootableEnemy::serialize(rtype::system::BinaryWriter& writer)
{
	writer << _life;
}

void ShootableEnemy::unserialize(rtype::system::BinaryReader& reader)
{
	int16_t life;

	reader >> life;
	if (life != _life)
	{
		setColor(_hitColor, _hitDuration);
		_life = life;
	}
}

void ShootableEnemy::onCollision(rtype::ecs::GameObject& collision)
{
	auto player = collision.getComponent<IPlayerShip>();
	if (player && player->hit())
	{
		doDamage(10);
		return;
	}

	auto enemy = collision.getComponent<IShootableEnemy>();
	if (enemy && enemy->team() != _team && _damage != 0)
	{
		enemy->doDamage(_damage);
		if (_manageDestruction)
			gameObject().destroy();
		incrementScore();
	}
}

int8_t ShootableEnemy::team() const
{
	return _team;
}

void ShootableEnemy::doDamage(int8_t damage)
{
	_life -= damage;
	if (_life <= 0)
	{
		if (_manageDestruction)
			gameObject().destroy();
		incrementScore();
	}
	else if (gameEngine().hasGraphics())
	{
		setColor(_hitColor, _hitDuration);
	}
}


void ShootableEnemy::setColor(const rtype::ecs::Color& color, float duration)
{
	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	if (renderer)
	{
		renderer->setColor(color);
		_colorDelay = duration;
	}
}

void ShootableEnemy::incrementScore()
{
	rtype::ecs::GameObject* obj = gameEngine().find("Score");
	if (obj)
	{
		auto score = obj->getComponent<IScore>();
		score->add(_score);
	}
}

int16_t ShootableEnemy::life() const
{
	return _life;
}
