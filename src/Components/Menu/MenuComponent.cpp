#include <iostream>
#include <stdexcept>
#include "MenuComponent.hpp"
#include "Components/Shader/IShader.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/TextInput/ITextInput.hpp"

static const int		idMenu_ = 0;
static const int		idOptions_ = 1;
static const int		idMultiplayers_ = 2;

RTYPE_COMPONENT_IMPL(MenuComponent)

MenuComponent::MenuComponent()
{
	_isTransition = false;
	_currMenuId = 0;
	_nextMenuId = 0;
	_keyboardSelect = 0;
	_playSoundSelect = 0;
	_timeAxis = 0.0f;
}

void	MenuComponent::start()
{
	gameEngine().createGameObject("menu/MenuBackground");
	gameEngine().createGameObject("menu/MenuTitle");

	gameEngine().createGameObject("menu/MenuOnePlayer");
	gameEngine().createGameObject("menu/MenuMultiplayer");
	gameEngine().createGameObject("menu/MenuOptions");

	gameEngine().createGameObject("menu/MenuVolume");
	gameEngine().createGameObject("menu/MenuVolumeCone");
	gameEngine().createGameObject("menu/MenuOptionsBack");

	gameEngine().createGameObject("menu/MenuIP");
	gameEngine().createGameObject("menu/MenuIPText");
	gameEngine().createGameObject("menu/MenuPort");
	gameEngine().createGameObject("menu/MenuPortText");
	gameEngine().createGameObject("menu/MenuIdRoom");
	gameEngine().createGameObject("menu/MenuIdRoomText");
	gameEngine().createGameObject("menu/MenuJoin");
	gameEngine().createGameObject("menu/MenuMultiplayersBack");

	gameEngine().createGameObject("menu/ParallaxMenu");
	gameEngine().createGameObject("menu/MenuLabel");
	organizeMenu();
}

rtype::ecs::GameObject *MenuComponent::configureNewButton(std::string const &name,
	int menuId, int linkMenuId)
{
	rtype::ecs::GameObject	*obj = gameEngine().find(name);

	if (!obj)
		throw std::runtime_error("Error : " + name + " not found in GameEngine");
	auto button = obj->getComponent<IButton>();
	if (button)
	{
		button->setMenuId(menuId);
		button->setLinkMenuId(linkMenuId);
	}
	return (obj);
}

void	MenuComponent::organizeMenu()
{
	std::vector<rtype::ecs::GameObject *>	menu;
	std::vector<rtype::ecs::GameObject *>	menuButton;

	_background = gameEngine().find("MenuBackground");

	// MAIN MENU
	menuButton.push_back(configureNewButton("MenuOnePlayer", 0, 0));
	menuButton.push_back(configureNewButton("MenuMultiplayer", idMenu_, idMultiplayers_));
	menuButton.push_back(configureNewButton("MenuOptions", idMenu_, idOptions_));
	menu.push_back(gameEngine().find("MenuOnePlayer"));
	menu.push_back(gameEngine().find("MenuMultiplayer"));
	menu.push_back(gameEngine().find("MenuOptions"));

	_menus.push_back(menu);
	menu.clear();
	_menusButton.push_back(menuButton);
	menuButton.clear();
	//END MAIN MENU

	// OPTIONS MENU
	menu.push_back(configureNewButton("MenuVolume", idOptions_, -1));
	menuButton.push_back(configureNewButton("MenuVolumeCone", idOptions_, -1));
	menu.push_back(gameEngine().find("MenuVolumeCone"));
	menuButton.push_back(configureNewButton("MenuOptionsBack", idOptions_, idMenu_));
	menu.push_back(gameEngine().find("MenuOptionsBack"));
	for (auto obj : menu)
		obj->setEnabled(false);
	_menus.push_back(menu);
	menu.clear();
	for (auto obj : menuButton)
		obj->setEnabled(false);
	_menusButton.push_back(menuButton);
	menuButton.clear();
	//END OPTIONS MENU

	// MULTIPLAYERS MENU
	menu.push_back(configureNewButton("MenuIP", idMultiplayers_, -1));
	menuButton.push_back(configureNewButton("MenuIPText", idMultiplayers_, -1));
	menu.push_back(gameEngine().find("MenuIPText"));
	menu.push_back(configureNewButton("MenuPort", idMultiplayers_, -1));
	menuButton.push_back(configureNewButton("MenuPortText", idMultiplayers_, -1));
	menu.push_back(gameEngine().find("MenuPortText"));
	menu.push_back(configureNewButton("MenuIdRoom", idMultiplayers_, -1));
	menuButton.push_back(configureNewButton("MenuIdRoomText", idMultiplayers_, -1));
	menu.push_back(gameEngine().find("MenuIdRoomText"));
	menuButton.push_back(configureNewButton("MenuJoin", idMultiplayers_, -1));
	menu.push_back(gameEngine().find("MenuJoin"));
	menuButton.push_back(configureNewButton("MenuMultiplayersBack", idMultiplayers_, idMenu_));
	menu.push_back(gameEngine().find("MenuMultiplayersBack"));

	for (auto obj : menu)
		obj->setEnabled(false);
	_menus.push_back(menu);
	menu.clear();
	for (auto obj : menuButton)
		obj->setEnabled(false);
	_menusButton.push_back(menuButton);
	menuButton.clear();
	//END MULTIPLAYERS MENU
}

void	MenuComponent::update()
{
  if (!_isTransition)
	{
	  mouseHandle();
	  for (std::vector<rtype::ecs::GameObject *> it : _menusButton)
	{
	  for (rtype::ecs::GameObject *obj : it)
		{
		  auto button = obj->getComponent<IButton>();

		  if (button)
		if (button->isClicked() && button->getLinkMenuId() >= 0)
		  changeMenu(button->getMenuId(), button->getLinkMenuId());
		}
	}
	}
  else
	{
	  if (isEndTransition())
	_isTransition = false;
	}
  _timeAxis -= gameEngine().getElapsedTime();
}

void	MenuComponent::mouseHandle()
{
  rtype::ecs::Vector2i	pos;

  if (!gameEngine().getInputs().onMouseMove(pos))
	{
	  int	count = 0;

	  for (auto it : _menusButton[_currMenuId])
	{
	  rtype::ecs::Vector2f	size = it->getComponent<ITransform>()->getSize();

	  if (size.x > 1.0f && size.y > 1.0f)
		_keyboardSelect = count;
	  count++;
	}
	  if (_keyboardSelect >= 0)
	deselect(_menusButton[_currMenuId][_keyboardSelect]);

	  rtype::ecs::IInput::key	key;
	  float						axis = gameEngine().getInputs().getJoystickAxis(rtype::ecs::IInput::axis::YAxis);
	  bool						aButton = gameEngine().getInputs().getJoystickButton(rtype::ecs::IInput::button::AButton);

	  if (axis < 70.0f && axis > -70.0f)
		  _timeAxis = 0.0f;
	  if (gameEngine().getInputs().onKeyDown(key)
		  || ((axis > 90.0f || axis < -90.0f) && _timeAxis <= 0.0f) || (aButton && _timeAxis <= 0.0f))
	  {
		  _timeAxis = 0.30f;
		  if (_keyboardSelect < 0)
			  _keyboardSelect = 0;
		  if (key == rtype::ecs::IInput::key::Down || axis > 90.0f)
			  _keyboardSelect = (_keyboardSelect + 1) % _menusButton[_currMenuId].size();
		  else if (key == rtype::ecs::IInput::key::Up || axis < -90.0f)
			  _keyboardSelect = ((_keyboardSelect > 0) ? _keyboardSelect - 1 : _menusButton[_currMenuId].size() - 1);
		  else if (key == rtype::ecs::IInput::key::Return || aButton)
			  validButton(_menusButton[_currMenuId][_keyboardSelect]);
	  }
	  if (_keyboardSelect >= 0)
		  select(_menusButton[_currMenuId][_keyboardSelect]);
	}
  else
	  _keyboardSelect = -1;
}

void	MenuComponent::validButton(rtype::ecs::GameObject *obj)
{
  auto	button = obj->getComponent<IButton>();
  auto	textInput = obj->getComponent<ITextInput>();

  if (button)
	button->setClicked(true);
  else if (textInput)
	textInput->setSelected(true);
}

void	MenuComponent::select(rtype::ecs::GameObject *obj)
{
	rtype::ecs::Vector2f		size(1.1f, 1.1f);

	obj->getComponent<ITransform>()->setSize(size);
}

void	MenuComponent::deselect(rtype::ecs::GameObject *obj)
{
	rtype::ecs::Vector2f		size(1.0f, 1.0f);

	obj->getComponent<ITransform>()->setSize(size);
}

void	MenuComponent::changeMenu(int currId, int nextId)
{
	_currMenuId = currId;
	_nextMenuId = nextId;
	_isTransition = true;
	_keyboardSelect = 0;

	gameEngine().getAudio().playSound("musics/clickMenu.ogg");

	auto		globalShader = gameObject().getComponent<IShader>();

	if (globalShader)
		globalShader->activate();
	else
		throw std::runtime_error("Error : " + gameObject().name() + " has no global shader");
}

bool	MenuComponent::isEndTransition()
{
	auto		globalShader = gameObject().getComponent<IShader>();

	if (globalShader)
	{
		if (globalShader->isAnim())
			return false;
	}
	else
		throw std::runtime_error("Error : " + gameObject().name() + " has no global shader");

	if (_currMenuId != _nextMenuId)
	{
		for (rtype::ecs::GameObject *obj : _menus[_currMenuId])
			obj->setEnabled(false);

		_currMenuId = _nextMenuId;
		for (rtype::ecs::GameObject *obj : _menus[_currMenuId])
			obj->setEnabled(true);
		globalShader->activate();
		return (false);
	}
	return (true);
}
