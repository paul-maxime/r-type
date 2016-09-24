#ifndef IPLAYERINPUTS_HPP_
#define IPLAYERINPUTS_HPP_

class IPlayerInputs
{
public:
	enum Key
	{
		MOVE_UP,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ATTACK,
		RELEASE,
		END_KEY
	};

	virtual ~IPlayerInputs() {}
	virtual bool isPressed(Key key) const = 0;
};


#endif // IPLAYERINPUTS_HPP_
