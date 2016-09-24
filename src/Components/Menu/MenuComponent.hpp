#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>

#include "RType/ECS/GameEngine.hpp"
#include "RType/ECS/AComponent.hpp"
#include "RType/ECS/GameObject.hpp"
#include "Components/Button/IButton.hpp"

RTYPE_PLUGIN
class MenuComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

public:
	MenuComponent();
	virtual ~MenuComponent() {}

	virtual void start();
	virtual void update();

private:
	void organizeMenu();
	void changeMenu(int currId, int nextId);
	bool isEndTransition();

	void select(rtype::ecs::GameObject *);
	void deselect(rtype::ecs::GameObject *);

	void mouseHandle();
	void validButton(rtype::ecs::GameObject *);

	rtype::ecs::GameObject *configureNewButton(std::string const &name,
		int menuId, int linkMenuId);

protected:
	std::vector< std::vector<rtype::ecs::GameObject *> >		_menus;
	std::vector< std::vector<rtype::ecs::GameObject *> >		_menusButton;
	rtype::ecs::GameObject		*_background;
	bool		_isTransition;

	int			_currMenuId;
	int			_nextMenuId;

	int			_keyboardSelect;
	int			_playSoundSelect;
	float		_timeAxis;
};

#endif // !MENU_HPP_
