#ifndef SPRITE_RENDERER_COMPONENT_HPP_
#define SPRITE_RENDERER_COMPONENT_HPP_

#include "RType/ECS/Rect.hpp"
#include "RType/ECS/AComponent.hpp"
#include "ISpriteRenderer.hpp"

RTYPE_PLUGIN
class SpriteRendererComponent : public rtype::ecs::AComponent, public ISpriteRenderer
{
	RTYPE_COMPONENT
public:
	virtual ~SpriteRendererComponent() {}

	virtual void start();
	virtual void draw();
	virtual void loadFile(rtype::ecs::file::Value const &);

	virtual void setSprite(const std::string& sprite, const rtype::ecs::IntRect& rect);
	virtual void setShader(IShader *shader);

	rtype::ecs::IntRect	const &getRect() const;
	void					  setRect(rtype::ecs::IntRect const&);

	virtual const rtype::ecs::Color& getColor() const;
	virtual void setColor(const rtype::ecs::Color& value);

private:
	std::string _sprite;
	rtype::ecs::IntRect _rect;
	rtype::ecs::Color _color;
	IShader *_shader;
	rtype::ecs::Vector3f _lerPos;
};

#endif // SPRITE_RENDERER_COMPONENT_HPP_
