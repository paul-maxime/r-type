#ifndef IANIMATIONS_HPP_
#define IANIMATIONS_HPP_

class IAnimations
{
public:
	virtual ~IAnimations() {}

	virtual void setSprite(const std::string& sprite) = 0;
	virtual void setSpeed(const std::string& animation, float speed) = 0;
	virtual float getSpeed(const std::string& animation) const = 0;
	virtual void setAnim(const std::string& animation) = 0;
	virtual void queueAnim(const std::string& animation) = 0;
	virtual bool isPlaying(const std::string& animation) const = 0;
	virtual bool willPlay(const std::string& animation) const = 0;
	virtual bool hasAnimation(const std::string& animation) const = 0;
	virtual bool hasPlayOnce() const = 0;
	virtual float getAnimationDuration(const std::string& animation) const = 0;
};

#endif /* !IANIMATIONS_HPP_ */
