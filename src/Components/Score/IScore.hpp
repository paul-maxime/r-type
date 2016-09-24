#ifndef ISCORE_HPP_
#define ISCORE_HPP_

class IScore
{
public:
	virtual ~IScore() {}

	virtual void add(uint32_t score) = 0;
};

#endif // ISCORE_HPP_
