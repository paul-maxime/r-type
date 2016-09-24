#ifndef		WAVESHADERCOMPONENT_HPP_
# define	WAVESHADERCOMPONENT_HPP_

#include "Components/Shader/IShader.hpp"
#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class WaveShaderComponent : public rtype::ecs::AComponent, IShader
{
	RTYPE_COMPONENT

public:
	WaveShaderComponent();
	virtual ~WaveShaderComponent() {}

	virtual void start();
	virtual void update();
	virtual void loadFile(const rtype::ecs::file::Value&);

	virtual void updateShader();
	virtual std::string const	&getName() const;
	virtual void activate();
	virtual bool isAnim() const { return _activate; }

private:
	std::string	_shader;

	float		_wave_phase;
	float		_wave_amplitudeX;
	float		_wave_amplitudeY;

	float		_waX;
	float		_waY;
	bool		_activate;
};

#endif /* !WAVESHADERCOMPONENT_HPP_ */
