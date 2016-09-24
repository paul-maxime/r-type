#ifndef FADE_OUT_COMPONENT_HPP_
#define FADE_OUT_COMPONENT_HPP_

#include <string>

#include "IFadeOut.hpp"
#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class FadeOutComponent : public rtype::ecs::AComponent, public IFadeOut
{
	RTYPE_COMPONENT
public:
	virtual ~FadeOutComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value& file);
	virtual void start();
	virtual void update();

	virtual float getDuration() const;

private:
	std::string _fadeAnimation;
	std::string _endAnimation;
	float _timer;
	float _duration;
};

#endif /* !FADE_OUT_COMPONENT_HPP_ */
