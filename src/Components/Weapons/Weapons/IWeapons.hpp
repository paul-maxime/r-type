#ifndef IWEAPONS_HPP_
#define IWEAPONS_HPP_

class IWeapons
{
public:
	virtual ~IWeapons() {}

	virtual void upgrade() = 0;
	virtual void addSpeed(float speed) = 0;
	virtual void addDamage(int8_t damage) = 0;
};

#endif /* !IWEAPONS_HPP_ */
