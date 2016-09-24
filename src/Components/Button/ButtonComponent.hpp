#ifndef		BUTTONCOMPONENT_HPP_
# define	BUTTONCOMPONENT_HPP_

#include <string>

#include "RType/ECS/AComponent.hpp"
#include "Components/Button/AbstractButton.hpp"

RTYPE_PLUGIN
class ButtonComponent : public AbstractButton
{
	RTYPE_COMPONENT

public:
	ButtonComponent();
	virtual ~ButtonComponent() {}

};

#endif /* !BUTTONCOMPONENT_HPP_ */
