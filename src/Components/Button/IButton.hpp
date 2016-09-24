#ifndef		IBUTTON_HPP_
# define	IBUTTON_HPP_

#include "RType/ECS/AComponent.hpp"

class IButton
{
public:
	virtual ~IButton() {}

	virtual bool isClicked() const = 0;
	virtual void setClicked(bool) = 0;

	virtual void setMenuId(int id) = 0;
	virtual void setLinkMenuId(int id) = 0;
	virtual int getMenuId() const = 0;
	virtual int getLinkMenuId() const = 0;
};

#endif /* !IBUTTON_HPP_ */
