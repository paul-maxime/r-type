#ifndef		ISHADER_HPP_
# define	ISHADER_HPP_

#include "RType/ECS/AComponent.hpp"

class IShader
{
public:
	virtual ~IShader() {}

	virtual void updateShader() = 0;
	virtual	std::string const &getName() const = 0;
	virtual	void activate() = 0;

	virtual bool isAnim() const = 0;

};

#endif /* !ISHADER_HPP_ */
