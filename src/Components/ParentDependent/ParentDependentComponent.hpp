#ifndef PARENT_DEPENDENT_COMPONENT_HPP_
#define PARENT_DEPENDENT_COMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class ParentDependentComponent : public rtype::ecs::AComponent
{
   RTYPE_COMPONENT
public:
	virtual ~ParentDependentComponent() {}

	virtual void start();
	virtual void update();

private:
	bool _hasParent;
};

#endif /* !PARENT_DEPENDENT_COMPONENT_HPP_ */
