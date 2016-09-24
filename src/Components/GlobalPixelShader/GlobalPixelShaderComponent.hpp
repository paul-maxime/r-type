#ifndef GLOBALPIXELSHADERCOMPONENT_HPP_
#define GLOBALPIXELSHADERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/Shader/IShader.hpp"

RTYPE_PLUGIN
class GlobalPixelShaderComponent : public rtype::ecs::AComponent, public IShader
{
	RTYPE_COMPONENT

private:
	std::string	_shader;
	float		_pixel_w;
	float		_pixel_h;

	float		_timer;
	float		_timeAnim;
	bool		_activate;
	float		_speed;

public:
	GlobalPixelShaderComponent();
	virtual ~GlobalPixelShaderComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();

	virtual bool isAnim() const;
	virtual void activate();
	virtual std::string const &getName() const;
	virtual void updateShader() {}
};

#endif // !GLOBALPIXELSHADERCOMPONENT_HPP_
