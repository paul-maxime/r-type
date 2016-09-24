#ifndef FORMATIONCOMPONENT_HPP_
#define FORMATIONCOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "Components/Transform/ITransform.hpp"

RTYPE_PLUGIN
class FormationComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	std::string _leaderName;
	std::list<std::string> _sbiresNames;

	rtype::ecs::Vector3f _leaderPos;
	std::list<rtype::ecs::Vector3f> _sbiresPos;

	std::weak_ptr<ITransform> _leaderT;
public:
	virtual ~FormationComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void draw();
};

#endif // !FORMATIONCOMPONENT_HPP_
