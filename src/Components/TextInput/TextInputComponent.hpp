#ifndef TEXTINPUTCOMPONENT_HPP_
#define TEXTINPUTCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/TextInput/ITextInput.hpp"

RTYPE_PLUGIN
class TextInputComponent : public rtype::ecs::AComponent, public ITextInput
{
	RTYPE_COMPONENT

public:
	TextInputComponent();
	virtual ~TextInputComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void draw();

	virtual void setSelected(bool selected);

private:
	virtual void selected();
	virtual void deselected();

	std::string	_spriteOn;
	std::string	_spriteOff;
	bool		_selected;

	std::string _string;

	rtype::ecs::IntRect _rect;
	rtype::ecs::Vector3f _lerPos;
};

#endif // !TEXTINPUTCOMPONENT_HPP_
