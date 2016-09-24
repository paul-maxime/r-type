#ifndef SHADERCOMPONENT_HPP_
#define SHADERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/Shader/IShader.hpp"

RTYPE_PLUGIN
class ShaderComponent : public rtype::ecs::AComponent, public IShader
{
	RTYPE_COMPONENT

public:
	ShaderComponent();
	virtual ~ShaderComponent();

	virtual void start();
	virtual void loadFile(const rtype::ecs::file::Value& file);

	virtual void updateShader();
	virtual std::string const &getName() const;
	virtual void activate();
	virtual bool isAnim() const { return false; }
private:
	std::string	_shader;
	std::string	_varText;
	std::unordered_map< std::string, float >		_values;
};

#endif // !SHADERCOMPONENT_HPP_
