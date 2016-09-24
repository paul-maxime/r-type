#ifndef BACKGROUND_COMPONENT_HPP_
#define BACKGROUND_COMPONENT_HPP_

#include <string>
#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class BackgroundComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	struct Background
	{
		std::string sprite;
		float speed;
		float pos;
		float size;
		rtype::ecs::Color color;
	};

public:
	virtual ~BackgroundComponent() {}

	virtual void start();
	virtual void update();
	virtual void draw();
	virtual void loadFile(const rtype::ecs::file::Value&);

private:
	std::vector<Background> _backgrounds;
};

#endif /* BACKGROUND_COMPONENT_HPP_ */
