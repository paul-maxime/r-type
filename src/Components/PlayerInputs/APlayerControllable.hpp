#ifndef APLAYERCONTROLLABLE_HPP_
#define APLAYERCONTROLLABLE_HPP_

#include <memory>

#include "IPlayerInputs.hpp"
#include "Components/Player/IPlayerComponent.hpp"

class APlayerControllable
{
private:
	std::weak_ptr<IPlayerInputs> _inputs;
	std::weak_ptr<IPlayerComponent> _player;

public:
	virtual ~APlayerControllable() {}

	virtual void setInputs(std::shared_ptr<IPlayerInputs> inputs)
	{
		_inputs = std::weak_ptr<IPlayerInputs>(inputs);
	}

	virtual std::shared_ptr<IPlayerInputs> getInputs()
	{
		return _inputs.lock();
	}

	virtual void setPlayer(std::shared_ptr<IPlayerComponent> player)
	{
		_player = std::weak_ptr<IPlayerComponent>(player);
	}

	virtual std::shared_ptr<IPlayerComponent> getPlayer()
	{
		return _player.lock();
	}

	virtual void addSpeed(float) {};
};

#endif // APLAYERCONTROLLABLE_HPP_
