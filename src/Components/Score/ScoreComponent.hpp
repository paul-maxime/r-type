#ifndef SCORECOMPONENT_HPP_
#define SCORECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/TextRenderer/ITextRenderer.hpp"
#include "IScore.hpp"

RTYPE_PLUGIN
class ScoreComponent : public rtype::ecs::AComponent, public IScore
{
	RTYPE_COMPONENT

private:
	std::weak_ptr<ITextRenderer> _renderer;
	uint32_t _score;

public:
	ScoreComponent();
	virtual ~ScoreComponent() {}

	virtual void start();
	virtual void serialize(rtype::system::BinaryWriter&);
	virtual void unserialize(rtype::system::BinaryReader&);

	virtual void add(uint32_t score);

private:
	void setText();

};

#endif // !SCORECOMPONENT_HPP_
