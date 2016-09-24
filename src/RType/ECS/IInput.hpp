#ifndef IINPUT_HPP_
#define IINPUT_HPP_

#include "Vector2.hpp"

namespace rtype
{
	namespace ecs
	{
		class IInput
		{
		public:
			enum key
			{
				Unknown = -1,
				A = 0,
				B,
				C,
				D,
				E,
				F,
				G,
				H,
				I,
				J,
				K,
				L,
				M,
				N,
				O,
				P,
				Q,
				R,
				S,
				T,
				U,
				V,
				W,
				X,
				Y,
				Z,
				Num0,
				Num1,
				Num2,
				Num3,
				Num4,
				Num5,
				Num6,
				Num7,
				Num8,
				Num9,
				Escape,
				LControl,
				LShift,
				LAlt,
				LSystem,
				RControl,
				RShift,
				RAlt,
				RSystem,
				Menu,
				LBracket,
				RBracket,
				SemiColon,
				Comma,
				Period,
				Quote,
				Slash,
				BackSlash,
				Tilde,
				Equal,
				Dash,
				Space,
				Return,
				BackSpace,
				Tab,
				PageUp,
				PageDown,
				End,
				Home,
				Insert,
				Delete,
				Add,
				Subtract,
				Multiply,
				Divide,
				Left,
				Right,
				Up,
				Down,
				Numpad0,
				Numpad1,
				Numpad2,
				Numpad3,
				Numpad4,
				Numpad5,
				Numpad6,
				Numpad7,
				Numpad8,
				Numpad9,
				F1,
				F2,
				F3,
				F4,
				F5,
				F6,
				F7,
				F8,
				F9,
				F10,
				F11,
				F12,
				F13,
				F14,
				F15,
				Pause,
				KeyCount
			};

			enum click
			{
				LeftClick,
				RightClick,
				MiddleClick,
				XButton1,
				XButton2,
				ButtonCount
			};

			enum button
			{
				AButton,
				BButton,
				XButton,
				YButton,
				LButton,
				RButton,
				Select,
				Start,
				LeftStick,
				RightStick
			};

			enum axis
			{
				XAxis,
				YAxis
			};

		public:
			virtual ~IInput() {};
			virtual bool keyPressed(IInput::key) = 0;
			virtual ecs::Vector2<float> mousePosition() = 0;
			virtual bool getClick(IInput::click) = 0;
			virtual bool getJoystickButton(IInput::button) = 0;
			virtual float getJoystickAxis(IInput::axis) = 0;
			virtual const std::string &getTypedString() = 0;
			virtual void setTypedString(const std::string &) = 0;

			virtual bool onKeyDown(ecs::IInput::key& key) = 0;
			virtual bool onKeyUp(ecs::IInput::key& key) = 0;
			virtual bool onMouseDown(ecs::IInput::click& button, ecs::Vector2i& pos) = 0;
			virtual bool onMouseUp(ecs::IInput::click& button, ecs::Vector2i& pos) = 0;
			virtual bool onMouseMove(ecs::Vector2i& pos) = 0;
			virtual bool onMouseMove() = 0;
		};
	} // namespace ecs
} // namespace rtype

#endif // IINPUT_HPP_
