#ifndef ANIMATIONS_COMPONENT_HPP_
#define ANIMATIONS_COMPONENT_HPP_

#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include "RType/ECS/AComponent.hpp"
#include "IAnimations.hpp"

RTYPE_PLUGIN
class AnimationsComponent : public rtype::ecs::AComponent, public IAnimations
{
	RTYPE_COMPONENT

private:
	struct Animation
	{
		float speed;
		std::vector<int> ids;
	};

private:
	static const float DEFAULT_ANIMATION_SPEED;

public:
	AnimationsComponent();
	virtual ~AnimationsComponent() {}

	virtual void start();
	virtual void update();
	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void serialize(rtype::system::BinaryWriter& writer);
	virtual void unserialize(rtype::system::BinaryReader& reader);

	virtual void setSprite(const std::string& sprite);
	virtual void setSpeed(const std::string& animation, float speed);
	virtual float getSpeed(const std::string& animation) const;
	virtual void setAnim(const std::string& animation);
	virtual void queueAnim(const std::string& animation);
	virtual bool isPlaying(const std::string& animation) const;
	virtual bool willPlay(const std::string& animation) const;
	virtual bool hasAnimation(const std::string& animation) const;
	virtual bool hasPlayOnce() const;
	virtual float getAnimationDuration(const std::string& animation) const;

private:
	void setRenderer(int id);

private:
	std::string _sprite;
	std::string _currentAnim;
	int _rows;
	int _columns;
	int _height;
	int _width;
	float _currentTime;
	std::unordered_map< std::string, Animation > _animations;
	std::list< std::string > _queue;
	bool _playedOnce;
};

#endif // !ANIMATIONS_COMPONENT_HPP_
