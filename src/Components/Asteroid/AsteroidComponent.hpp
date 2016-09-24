#ifndef ASTEROIDCOMPONENT_HPP_
#define ASTEROIDCOMPONENT_HPP_

#include <vector>
#include <string>

#include "RType/ECS/AComponent.hpp"
#include "IAsteroid.hpp"

RTYPE_PLUGIN
class AsteroidComponent : public rtype::ecs::AComponent, public IAsteroid
{
	RTYPE_COMPONENT

private:
	std::vector<std::string> _sprites;
	std::string _child;
	int8_t _index;

public:
	virtual ~AsteroidComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void stop();
	virtual void serialize(rtype::system::BinaryWriter& writer);
	virtual void unserialize(rtype::system::BinaryReader& reader);

	virtual void setIndex(int8_t index);
};

#endif // !ASTEROIDCOMPONENT_HPP_
