#ifndef IPLAYERSHIP_HPP_
#define IPLAYERSHIP_HPP_

class IPlayerShip
{
public:
	virtual ~IPlayerShip() {}

	virtual bool hit() = 0;
};

#endif // IPLAYERSHIP_HPP_
