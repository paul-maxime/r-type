#ifndef GLOBALBLINKSHADERCOMPONENT_HPP_
#define GLOBALBLINKSHADERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/Shader/IShader.hpp"

RTYPE_PLUGIN
class GlobalBlinkShaderComponent : public rtype::ecs::AComponent, public IShader
{
	RTYPE_COMPONENT

private:
	std::string	_shader;
	float		_blink_alpha;

	float		_timer;
	float		_timeAnim;
	bool		_activate;
public:
	GlobalBlinkShaderComponent();
	virtual ~GlobalBlinkShaderComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();

	virtual bool isAnim() const;
	virtual void activate();
	virtual std::string const &getName() const;
	virtual void updateShader() {}
};

#endif // !GLOBALBLINKSHADERCOMPONENT_HPP_
