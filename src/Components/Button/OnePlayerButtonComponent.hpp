#ifndef		ONEPLAYERBUTTONCOMPONENT_HPP_
# define	ONEPLAYERBUTTONCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/Button/AbstractButton.hpp"

RTYPE_PLUGIN
class OnePlayerButtonComponent : public AbstractButton
{
	RTYPE_COMPONENT

public:
	OnePlayerButtonComponent();
	virtual ~OnePlayerButtonComponent() {}

	virtual void update();

private:
	float		_timer;
	bool		_launch;
};

#endif /* !ONEPLAYERBUTTONCOMPONENT_HPP_ */
