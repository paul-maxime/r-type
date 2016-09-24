#ifndef TEXTRENDERERCOMPONENT_HPP_
#define TEXTRENDERERCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "ITextRenderer.hpp"

RTYPE_PLUGIN
class TextRendererComponent : public rtype::ecs::AComponent, public ITextRenderer
{
	RTYPE_COMPONENT

private:
	std::string _font;
	std::string _text;
	std::string _subtext;
	uint32_t _size;
	rtype::ecs::Color _color;
	bool _shadow;
	bool _subline;
	rtype::ecs::Vector2f _delta;

public:
	virtual ~TextRendererComponent() {}

	virtual void start();
	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void draw();

	virtual void setText(const std::string& text);
	virtual const std::string &getText() const;

private:
	void draw(const std::string& text, uint32_t size);
};

#endif // !TEXTRENDERERCOMPONENT_HPP_
