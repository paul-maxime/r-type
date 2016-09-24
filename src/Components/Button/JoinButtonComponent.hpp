#ifndef		JOINBUTTONCOMPONENT_HPP_
# define	JOINBUTTONCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/Button/AbstractButton.hpp"

RTYPE_PLUGIN
class JoinButtonComponent : public AbstractButton
{
	RTYPE_COMPONENT

public:
	virtual ~JoinButtonComponent() {}

	virtual void update();
};

#endif /* !JOINBUTTONCOMPONENT_HPP_ */
