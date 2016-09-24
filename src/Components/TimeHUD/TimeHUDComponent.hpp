#ifndef TIMEHUDCOMPONENT_HPP_
#define TIMEHUDCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/TextRenderer/ITextRenderer.hpp"

RTYPE_PLUGIN
class TimeHUDComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::string	_circle;
	std::string _littleCircle;
	float		_timerS;
	float		_timer;
	float		_rota;

	rtype::ecs::Vector3f		_pos;
	std::weak_ptr<ITextRenderer> _renderer;

	void setText();

public:
	virtual ~TimeHUDComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void draw();
};

#endif // !TIMEHUDCOMPONENT_HPP_
