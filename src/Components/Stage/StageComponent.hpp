#ifndef STAGECOMPONENT_HPP_
#define STAGECOMPONENT_HPP_

#include "RType/ECS/AComponent.hpp"
#include "IStage.hpp"

RTYPE_PLUGIN
class StageComponent : public rtype::ecs::AComponent, public IStage
{
	RTYPE_COMPONENT

private:
	struct StageAction
	{
		std::string entity;
		float x;
		float y;
		float time;
		float speedX;
		float speedY;
		bool hasSpeed;
	};

	std::string _name;
	std::vector<StageAction> _actions;
	std::string _nextStage;

	std::list<rtype::ecs::GameObject*> _aliveEntities;
	size_t _currentAction;
	float _currentTime;

	std::shared_ptr<std::function<void (rtype::ecs::GameObject&)>> _onEntityDestroy;

public:
	virtual ~StageComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();

	virtual const std::string& name() const;

private:
	void onEntityDestroy(rtype::ecs::GameObject& sender);
};

#endif // !STAGECOMPONENT_HPP_
