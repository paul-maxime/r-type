#ifndef FORCE_HPP_
# define FORCE_HPP_

class AForce
{
public:
	AForce() : _rot(0), _taken(false)
	{
	}

	virtual ~AForce() {}

protected:
	float _rot;
	bool _taken;

public:
	virtual size_t getInstanceId() = 0;
	void setRotation(float rotation) { _rot = rotation; };

	virtual void release() = 0;
};

#endif
