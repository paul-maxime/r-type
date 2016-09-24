#ifndef ASTEROIDSPAWNERCOMPONENT_HPP_
#define ASTEROIDSPAWNERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class AsteroidSpawnerComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::vector<std::string> _models;
	float _minDelay;
	float _maxDelay;
	float _nextDelay;

public:
	virtual ~AsteroidSpawnerComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();

private:
	void spawnAsteroid();
};

#endif // !ASTEROIDSPAWNERCOMPONENT_HPP_
