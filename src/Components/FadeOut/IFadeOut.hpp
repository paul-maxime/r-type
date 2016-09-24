#ifndef IFADE_OUT_HPP_
#define IFADE_OUT_HPP_

class IFadeOut
{
public:
	virtual ~IFadeOut() {}

	virtual float getDuration() const = 0;
};

#endif /* !IFADE_OUT_HPP_ */
