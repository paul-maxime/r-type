#include "RType/ECS/GameEngine.hpp"
#include "Components/DestroyEvent/IDestroyEvent.hpp"
#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "PlayerComponent.hpp"

RTYPE_COMPONENT_IMPL(PlayerComponent)

void PlayerComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_shipName = file.getString("ship");
	_lives = file.getInt("lives");
	_lifeTexture = file.getString("lifeTexture");
	_ship = nullptr;
	_damage = 0;
}

void PlayerComponent::start()
{
	if (gameEngine().hasGraphics())
	{
		_lifeTextureSize = gameEngine().getGraphics().getSize(_lifeTexture);
	}

	auto inputsObj = gameEngine().find(gameObject().name() + "Inputs");
	if (!inputsObj)
		throw std::runtime_error("error: Player doesn't have any linked input object.");

	auto inputs = inputsObj->getComponent<IPlayerInputs>();
	if (!inputs)
		throw std::runtime_error("error: PlayerInputs doesn't have an input component.");
	_inputs = std::weak_ptr<IPlayerInputs>(inputs);

	if (!gameObject().isLocal()) return;

	spawnShip();
}

void PlayerComponent::stop()
{
	if (!gameObject().isLocal()) return;

	_onShipDestroy.reset();
	if (_ship)
		_ship->destroy();
}

void PlayerComponent::onGUI()
{
	if (_lifeTexture == "") return;

	if (!gameObject().isLocal())
	{
		auto inputs = _inputs.lock();
		if (!inputs || !std::dynamic_pointer_cast<AComponent>(inputs)->gameObject().isOwner()) return;
	}

	for (int8_t i = 0; i < _lives && i < 3; ++i)
	{
		rtype::ecs::Vector3f pos(-1.0f * static_cast<float>(i) * (static_cast<float>(_lifeTextureSize.x) + 10.0f) + 960.0f,
			20.0f, 0.0f);

		gameEngine().getGraphics().draw(_lifeTexture, pos);
	}
}

void PlayerComponent::serialize(rtype::system::BinaryWriter& writer)
{
	writer << _lives << _damage;
}

void PlayerComponent::unserialize(rtype::system::BinaryReader& reader)
{
	reader >> _lives >> _damage;
}

void PlayerComponent::addLife()
{
	++_lives;
}

void PlayerComponent::addSpeed(float speed)
{
	auto t = _ship->name();
	std::shared_ptr<APlayerControllable> ptr = _ship->getComponent<APlayerControllable>();

	ptr->addSpeed(speed);
}

void PlayerComponent::spawnShip()
{
	_ship = gameEngine().createGameObject(_shipName);

	auto controllable = _ship->getComponent<APlayerControllable>();
	if (!controllable)
		throw std::runtime_error("error: PlayerShip doesn't have any controllable component.");
	controllable->setInputs(_inputs.lock());
	controllable->setPlayer(gameObject().getComponent<PlayerComponent>());

	auto event = _ship->getComponent<IDestroyEvent>();
	if (!event)
		throw std::runtime_error("error: PlayerShip doesn't have a DestroyEvent component.");
	_onShipDestroy = std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>>
		(new std::function<void (rtype::ecs::GameObject&)>
			(std::bind(&PlayerComponent::onShipDestroy, this, std::placeholders::_1)));
	event->subscribe(_onShipDestroy);
}

void PlayerComponent::onShipDestroy(rtype::ecs::GameObject&)
{
	--_lives;
	_ship = nullptr;
	if (_lives >= 0)
	{
		spawnShip();
	}
}

void PlayerComponent::setDamage(int8_t damage)
{
	_damage = damage;
}

void PlayerComponent::setLives(int8_t lives)
{
	_lives = lives;
}

int8_t PlayerComponent::getDamage()
{
	return (_damage);
}
