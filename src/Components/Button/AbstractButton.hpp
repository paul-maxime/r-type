#ifndef		ABSTRACTBUTTON_HPP_
# define	ABSTRACTBUTTON_HPP_

#include <string>

#include "RType/ECS/AComponent.hpp"
#include "Components/Button/IButton.hpp"

class AbstractButton : public rtype::ecs::AComponent, public IButton
{

public:
	AbstractButton();
	virtual ~AbstractButton() {}

	virtual void update();

	virtual bool isClicked() const;
	virtual void setClicked(bool click);
	virtual void setMenuId(int id);
	virtual void setLinkMenuId(int id);
	virtual int getMenuId() const;
	virtual int getLinkMenuId() const;
	virtual void selected();
	virtual void deselected();

protected:

	int _menuId;
	int _linkMenuId;

	bool _click;
};

#endif /* !ABSTRACTBUTTON_HPP_ */
