#ifndef ISTAGE_HPP_
#define ISTAGE_HPP_

class IStage
{
public:
	virtual ~IStage() {}

	virtual const std::string& name() const = 0;
};

#endif // ISTAGE_HPP_
