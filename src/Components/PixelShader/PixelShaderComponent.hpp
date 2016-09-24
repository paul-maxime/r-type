#ifndef		PIXELSHADERCOMPONENT_HPP_
# define	PIXELSHADERCOMPONENT_HPP_

#include "Components/Shader/IShader.hpp"
#include "RType/ECS/AComponent.hpp"
#include "RType/ECS/Rect.hpp"

RTYPE_PLUGIN
class PixelShaderComponent : public rtype::ecs::AComponent, public IShader
{
	RTYPE_COMPONENT

public:
	PixelShaderComponent();
	virtual ~PixelShaderComponent() {}

	virtual void start();
	virtual void update();
	virtual void loadFile(const rtype::ecs::file::Value& file);

	virtual void updateShader();
	virtual std::string const &getName() const;
	virtual void activate();
	virtual bool isAnim() const;

private:
	std::string	_shader;
	float		_pixel_w;
	float		_pixel_h;
	rtype::ecs::IntRect _rect;

	float		_timer;
	float		_timeAnim;
	bool		_activate;
	float		_speed;
};

#endif /* !PIXELSHADERCOMPONENT_HPP_ */
