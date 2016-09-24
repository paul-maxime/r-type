#ifndef IBULLET_HPP_
#define IBULLET_HPP_

class IBullet
{
public:
	virtual ~IBullet() {}

	virtual void setDamage(int8_t damage) = 0;
};

#endif /* !IBULLET_HPP_ */
