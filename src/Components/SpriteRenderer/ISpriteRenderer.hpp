#ifndef ISPRITERENDERER_HPP_
#define ISPRITERENDERER_HPP_

#include "RType/ECS/Rect.hpp"
#include "RType/ECS/Color.hpp"
#include "Components/Shader/IShader.hpp"

class ISpriteRenderer
{
public:
	virtual ~ISpriteRenderer() {}

	virtual void setSprite(const std::string& sprite, const rtype::ecs::IntRect& rect) = 0;
	virtual void setShader(IShader *shader) = 0;

	virtual rtype::ecs::IntRect const	&getRect() const = 0;
	virtual void						setRect(rtype::ecs::IntRect const&) = 0;

	virtual const rtype::ecs::Color& getColor() const = 0;
	virtual void setColor(const rtype::ecs::Color& value) = 0;
};

#endif // ISPRITERENDERER_HPP_
