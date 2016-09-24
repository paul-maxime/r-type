#ifndef TEMPLATECOMPONENT_HPP_
#define TEMPLATECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class TemplateComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:

public:
	virtual ~TemplateComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void draw();
};

#endif // !TEMPLATECOMPONENT_HPP_
