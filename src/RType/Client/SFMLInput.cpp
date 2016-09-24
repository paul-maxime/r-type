#include <iostream>

#include "SFMLInput.hpp"

namespace rtype
{
	namespace client
	{
		SFMLInput::SFMLInput(sf::RenderWindow &window) : _window(window)
		{
			_click[ecs::IInput::LeftClick] = sf::Mouse::Left;
			_click[ecs::IInput::RightClick] = sf::Mouse::Right;

			_joystick[ecs::IInput::AButton] = 0;
			_joystick[ecs::IInput::BButton] = 1;
			_joystick[ecs::IInput::XButton] = 2;
			_joystick[ecs::IInput::YButton] = 3;
			_joystick[ecs::IInput::LButton] = 4;
			_joystick[ecs::IInput::RButton] = 5;
			_joystick[ecs::IInput::Select] = 6;
			_joystick[ecs::IInput::Start] = 7;
			_joystick[ecs::IInput::LeftStick] = 8;
			_joystick[ecs::IInput::RightStick] = 9;

			_axis[ecs::IInput::XAxis] = sf::Joystick::Axis::X;
			_axis[ecs::IInput::YAxis] = sf::Joystick::Axis::Y;

		}

		bool SFMLInput::keyPressed(ecs::IInput::key key)
		{
			return (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key)));
		}

		ecs::Vector2f SFMLInput::mousePosition()
		{
			sf::Vector2u window = _window.getSize();
			sf::Vector2f view = _window.getView().getSize();
			sf::Vector2i mouse = sf::Mouse::getPosition(_window);

			ecs::Vector2f windowf(static_cast<float>(window.x), static_cast<float>(window.y));
			ecs::Vector2f mousef(static_cast<float>(mouse.x), static_cast<float>(mouse.y));

			mousef.x = mousef.x * view.x / windowf.x;
			mousef.y = mousef.y * view.y / windowf.y;

			return mousef;
		}

		bool SFMLInput::getClick(ecs::IInput::click click)
		{
			return (sf::Mouse::isButtonPressed(_click[click]));
		}

		bool SFMLInput::getJoystickButton(ecs::IInput::button button)
		{
			for (unsigned int joystick = 0; joystick < 3; ++joystick)
			{
				if (sf::Joystick::isConnected(joystick))
					return (sf::Joystick::isButtonPressed(joystick, _joystick[button]));
			}
			return false;
		}

		float SFMLInput::getJoystickAxis(ecs::IInput::axis axis)
		{
			for (unsigned int joystick = 0; joystick < 3; ++joystick)
			{
				if (sf::Joystick::isConnected(joystick))
					return (sf::Joystick::getAxisPosition(joystick, _axis[axis]));
			}
			return 0.f;
		}

		const std::string &SFMLInput::getTypedString()
		{
			return (_typedString);
		}

		void SFMLInput::setTypedString(const std::string &str)
		{
			_typedString = str;
		}

		bool SFMLInput::onKeyDown(ecs::IInput::key& key)
		{
			for (auto it = _events.begin(); it != _events.end(); ++it)
			{
				if (it->type == sf::Event::KeyPressed)
				{
					key = static_cast<ecs::IInput::key>(it->key.code);
					return true;
				}
			}
			return false;
		}

		bool SFMLInput::onKeyUp(ecs::IInput::key& key)
		{
			for (auto it = _events.begin(); it != _events.end(); ++it)
			{
				if (it->type == sf::Event::KeyReleased)
				{
					key = static_cast<ecs::IInput::key>(it->key.code);
					return true;
				}
			}
			return false;
		}

		bool SFMLInput::onMouseDown(ecs::IInput::click& button, ecs::Vector2i& pos)
		{
			for (auto it = _events.begin(); it != _events.end(); ++it)
			{
				if (it->type == sf::Event::MouseButtonPressed)
				{
					pos = ecs::Vector2i(it->mouseButton.x, it->mouseButton.y);
					button = static_cast<ecs::IInput::click>(it->mouseButton.button);
					return true;
				}
			}
			return false;
		}

		bool SFMLInput::onMouseUp(ecs::IInput::click& button, ecs::Vector2i& pos)
		{
			for (auto it = _events.begin(); it != _events.end(); ++it)
			{
				if (it->type == sf::Event::MouseButtonReleased)
				{
					pos = ecs::Vector2i(it->mouseButton.x, it->mouseButton.y);
					button = static_cast<ecs::IInput::click>(it->mouseButton.button);
					return true;
				}
			}
			return false;
		}

		bool SFMLInput::onMouseMove(ecs::Vector2i& pos)
		{
			for (auto it = _events.begin(); it != _events.end(); ++it)
			{
				if (it->type == sf::Event::MouseMoved)
				{
					pos = ecs::Vector2i(it->mouseMove.x, it->mouseMove.y);
					return true;
				}
			}
			return false;
		}

		bool SFMLInput::onMouseMove()
		{
			for (auto it = _events.begin(); it != _events.end(); ++it)
			{
				if (it->type == sf::Event::MouseMoved)
					return true;
			}
			return false;
		}

		void SFMLInput::setEvents(const std::list<sf::Event>& events)
		{
			_events = events;
		}
	} // namespace ecs
} // namespace rtype
