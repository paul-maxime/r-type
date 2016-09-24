#ifndef IASTEROID_HPP_
#define IASTEROID_HPP_

class IAsteroid
{
public:
	virtual ~IAsteroid() {}

	virtual void setIndex(int8_t index) = 0;
};

#endif // IASTEROID_HPP_
