#include <iostream>
#include <cmath>

#include "Components/SpriteRenderer/ISpriteRenderer.hpp"
#include "RType/ECS/GameEngine.hpp"
#include "AnimationsComponent.hpp"

const float AnimationsComponent::DEFAULT_ANIMATION_SPEED = 0.5f;

RTYPE_COMPONENT_IMPL(AnimationsComponent)

AnimationsComponent::AnimationsComponent()
{
	_currentTime = 0;
}

void AnimationsComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_sprite = file.getString("sprite");
	_rows = file.getInt("rows");
	_columns = file.getInt("columns");
	_currentAnim = file.getString("default");

	if (file.hasField("animations"))
	{
		for (const std::string& name : file["animations"].fieldNames())
		{
			const rtype::ecs::file::Value sub = file["animations"][name];
			Animation anim;
			if (file.hasField("animations_speed") &&
				file["animations_speed"].hasField(name))
				anim.speed = file["animations_speed"][name].asFloat();
			else
				anim.speed = DEFAULT_ANIMATION_SPEED;
			for (size_t i = 0; i < sub.size(); ++i)
			{
				anim.ids.push_back(file["animations"][name][i].asInt());
			}
			_animations[name] = anim;
		}
	}
	if (_currentAnim != "" && _animations.find(_currentAnim) == _animations.end())
	{
		_currentAnim = "";
		std::cerr << "Warning: 'default' in AnimationsComponent does not have a known value." << std::endl;
	}
	if (_rows <= 0)
		_rows = 1;
	if (_columns <= 0)
		_columns = 1;
}

void AnimationsComponent::start()
{
	_playedOnce = false;

	if (!gameEngine().hasGraphics()) return;

	rtype::ecs::Vector2u size = gameEngine().getGraphics().getSize(_sprite);
	_height = size.y / _rows;
	_width = size.x / _columns;
	if (_currentAnim != "")
	{
		setRenderer(_animations[_currentAnim].ids.size() ? _animations[_currentAnim].ids[0] : 0);
	}
}

void AnimationsComponent::update()
{
	if (_currentAnim != "" && _animations[_currentAnim].speed > 0 &&
		_animations[_currentAnim].ids.size())
	{
		float tot = _animations[_currentAnim].ids.size() * _animations[_currentAnim].speed;

		size_t index = static_cast<size_t>(std::floor(_currentTime / _animations[_currentAnim].speed));
		int prevIdx = index < _animations[_currentAnim].ids.size() ? _animations[_currentAnim].ids[index] : _animations[_currentAnim].ids[_animations[_currentAnim].ids.size() - 1];

		if ((_currentTime += gameEngine().getElapsedTime()) >= tot)
		{
			_playedOnce = true;
			_currentTime = std::fmod(_currentTime, tot);
			if (_queue.size())
			{
				setAnim(_queue.front());
				_queue.pop_front();
				if (_animations[_currentAnim].speed <= 0 || !_animations[_currentAnim].ids.size())
					return ;
			}
		}
		index = static_cast<size_t>(std::floor(_currentTime / _animations[_currentAnim].speed));
		int idx = index < _animations[_currentAnim].ids.size() ? _animations[_currentAnim].ids[index] : _animations[_currentAnim].ids[_animations[_currentAnim].ids.size() - 1];

		if (prevIdx != idx)
		{
			setRenderer(idx);
		}
	}
}

void AnimationsComponent::serialize(rtype::system::BinaryWriter& writer)
{
	if (_animations.size() < 2) return;

	writer << _currentAnim;
	writer << static_cast<uint8_t>(_queue.size());
	for (const std::string& anim : _queue)
		writer << anim;
}

void AnimationsComponent::unserialize(rtype::system::BinaryReader& reader)
{
	if (_animations.size() < 2) return;

	std::string currentAnim;
	uint8_t queueSize;
	std::list<std::string> queue;

	reader >> currentAnim >> queueSize;
	for (uint8_t i = 0; i < queueSize; ++i)
	{
		std::string anim;
		reader >> anim;
		queue.push_back(anim);
	}

	if (currentAnim != _currentAnim)
		setAnim(currentAnim);
	if (_queue.size() != queue.size())
		_queue = queue;
}

void AnimationsComponent::setSprite(const std::string& sprite)
{
	_sprite = sprite;
}

void AnimationsComponent::setSpeed(const std::string& animation, float speed)
{
	std::unordered_map< std::string, Animation >::iterator it;

	if ((it = _animations.find(animation)) == _animations.end())
		return ;
	it->second.speed = speed;
}

float AnimationsComponent::getSpeed(const std::string& animation) const
{
	auto it = _animations.find(animation);
	if (it == _animations.end())
		return -1;
	return it->second.speed;
}

void AnimationsComponent::setAnim(const std::string& animation)
{
	if (_animations.find(animation) == _animations.end())
		return ;
	_currentAnim = animation;
	_currentTime = 0;
	_playedOnce = false;
}

void AnimationsComponent::queueAnim(const std::string& animation)
{
	if (_animations.find(animation) != _animations.end())
		_queue.push_back(animation);
}

bool AnimationsComponent::isPlaying(const std::string& animation) const
{
	return (_currentAnim == animation);
}

bool AnimationsComponent::willPlay(const std::string& animation) const
{
	return (_currentAnim == animation ||
			std::find(_queue.begin(), _queue.end(), animation) != _queue.end());
}

void AnimationsComponent::setRenderer(int id)
{
	auto c = gameObject().getComponent<ISpriteRenderer>();
	if (c)
	{
		c->setSprite(_sprite, rtype::ecs::IntRect((id % _columns) * _width, (id / _columns) * _height, _width, _height));
	}
}

bool AnimationsComponent::hasAnimation(const std::string& animation) const
{
	return (_animations.find(animation) != _animations.end());
}

float AnimationsComponent::getAnimationDuration(const std::string& animation) const
{
	if (_animations.find(animation) == _animations.end())
		return (0);
	return (_animations.at(animation).ids.size() * _animations.at(animation).speed);
}

bool AnimationsComponent::hasPlayOnce() const
{
	return (_playedOnce);
}
