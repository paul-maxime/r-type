#ifndef KONAMICODECOMPONENT_HPP_
#define KONAMICODECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "RType/ECS/IInput.hpp"

RTYPE_PLUGIN
class KonamiCodeComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::vector<rtype::ecs::IInput::key>		_code;
	unsigned int								_it;
public:
	KonamiCodeComponent();
	virtual ~KonamiCodeComponent() {}

	virtual void update();
};

#endif // !KONAMICODECOMPONENT_HPP_
