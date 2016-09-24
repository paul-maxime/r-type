#include <iostream>
#include "RType/ECS/GameEngine.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/Animations/IAnimations.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "Components/PlayerInputs/IPlayerInputs.hpp"
#include "Components/PlayerColorize/IPlayerColorize.hpp"
#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "PlayerShipComponent.hpp"

RTYPE_COMPONENT_IMPL(PlayerShipComponent)

void PlayerShipComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_explosion = file.getString("explosion");

	if (file.hasField("explosionPos"))
	{
		_explosionDelta = rtype::ecs::Vector3f
			(file["explosionPos"][0].asFloat(), file["explosionPos"][1].asFloat(), 0.0f);
	}
	if (file.hasField("ships"))
	{
		for (size_t i = 0; i < file["ships"].size(); i++)
			_shipName.push_back(file["ships"][i].asString());
	}
}

void PlayerShipComponent::start()
{
	_invulnerabilityTime = 3.0;

	if (gameObject().isLocal())
	{
		auto objColorize = gameEngine().find("GameScene");
		if (objColorize)
		{
			auto colorize = objColorize->getComponent<IPlayerColorize>();
			if (colorize)
			{
				if (gameObject().getComponent<APlayerControllable>())
				{
					size_t _playerId = std::dynamic_pointer_cast<AComponent>(gameObject().getComponent<APlayerControllable>()->getPlayer())->gameObject().instanceId();
					_spriteID = colorize->sprite(_playerId, _shipName.size());
					auto animation = gameObject().getComponent<IAnimations>();
					if (animation && _spriteID < _shipName.size())
					{
						animation->setSprite(_shipName[_spriteID]);
					}
				}
			}
		}
	}

	auto renderer = gameObject().getComponent<ISpriteRenderer>();
	if (renderer)
	{
		_originalColor = renderer->getColor();
	}

	_isCurrentPlayer = false;
	auto inputs = gameObject().getComponent<IPlayerInputs>();

	if (gameObject().isLocal() ||
		(inputs && std::dynamic_pointer_cast<AComponent>(inputs)->gameObject().isOwner()))
		_isCurrentPlayer = true;
}

void PlayerShipComponent::update()
{
	if (!gameObject().isLocal())
	{
		auto animation = gameObject().getComponent<IAnimations>();
		if (animation && _spriteID < _shipName.size())
		{
			animation->setSprite(_shipName[_spriteID]);
		}
	}
	if (_invulnerabilityTime > 0.0f)
	{
		_invulnerabilityTime -= gameEngine().getElapsedTime();
		blink();
	}
}

bool PlayerShipComponent::hit()
{
	if (_invulnerabilityTime > 0)
		return false;
	spawnExplosion();
	gameObject().destroy();
	return true;
}

void PlayerShipComponent::blink()
{
	if (!gameEngine().hasGraphics()) return;

	auto renderer = gameObject().getComponent<ISpriteRenderer>();

	if (!renderer) return;

	if (_invulnerabilityTime > 0.0f)
	{
		auto renderer = gameObject().getComponent<ISpriteRenderer>();
		if (static_cast<int>(_invulnerabilityTime * 1000.0f) % 200 < 100)
			renderer->setColor(rtype::ecs::Color(64,
					_originalColor.r, _originalColor.g, _originalColor.b));
		else
			renderer->setColor(_originalColor);
	}
	else
	{
		renderer->setColor(_originalColor);
	}
}

void PlayerShipComponent::spawnExplosion()
{
	if (!_explosion.empty())
	{
		rtype::ecs::GameObject* explosion = gameEngine().createGameObject(_explosion);
		auto newTransform = explosion->getComponent<ITransform>();
		auto myTransform = gameObject().getComponent<ITransform>();
		if (newTransform && myTransform)
			newTransform->setPosition(myTransform->getAbsolutePosition() + _explosionDelta);
	}
}

void PlayerShipComponent::serialize(rtype::system::BinaryWriter& writer)
{
	writer << _spriteID;
}

void PlayerShipComponent::unserialize(rtype::system::BinaryReader& reader)
{
	reader >> _spriteID;
}
