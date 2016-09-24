#ifndef RTYPE_CLIENT_SFMLINPUT_HPP_
#define RTYPE_CLIENT_SFMLINPUT_HPP_

#include <list>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "RType/ECS/IInput.hpp"
#include "RType/ECS/Vector2.hpp"

namespace rtype
{
	namespace client
	{
		class SFMLInput : public ecs::IInput
		{
		public:
			SFMLInput(sf::RenderWindow &);
			virtual ~SFMLInput() {}

		private:
			std::string _typedString;
			sf::RenderWindow &_window;
			std::unordered_map<int, sf::Mouse::Button> _click;
			std::unordered_map<int, int> _joystick;
			std::unordered_map<int, sf::Joystick::Axis> _axis;
			std::list<sf::Event> _events;

		public:
			virtual bool keyPressed(ecs::IInput::key);
			virtual ecs::Vector2f mousePosition();
			virtual bool getClick(ecs::IInput::click);
			virtual bool getJoystickButton(ecs::IInput::button);
			virtual float getJoystickAxis(ecs::IInput::axis);
			virtual const std::string &getTypedString();
			virtual void setTypedString(const std::string &);

			virtual bool onKeyDown(ecs::IInput::key& key);
			virtual bool onKeyUp(ecs::IInput::key& key);
			virtual bool onMouseDown(ecs::IInput::click& button, ecs::Vector2i& pos);
			virtual bool onMouseUp(ecs::IInput::click& button, ecs::Vector2i& pos);
			virtual bool onMouseMove(ecs::Vector2i& pos);
			virtual bool onMouseMove();

			void setEvents(const std::list<sf::Event>& events);
		};
	} // namespace client
} // namespace rtype

#endif // RTYPE_CLIENT_SFMLINPUT_HPP_
