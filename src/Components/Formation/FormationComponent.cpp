#include "RType/ECS/GameEngine.hpp"
#include "FormationComponent.hpp"

RTYPE_COMPONENT_IMPL(FormationComponent)

void FormationComponent::loadFile(const rtype::ecs::file::Value& file)
{
	_leaderName = file["leader"].asString();
	if (file.hasField("leaderPos"))
	{
		auto pos = file["leaderPos"];
		_leaderPos.x = pos[0].asFloat();
		_leaderPos.y = pos[0].asFloat();
	}
	if (file.hasField("sbires"))
	{
		if (!file.hasField("sbiresPositions"))
			throw std::runtime_error("your sbires should have a position");
		auto sbires = file["sbires"];
		auto sbiresPos = file["sbiresPositions"];
		if (sbires.size() != sbiresPos.size() / 3)
			throw std::runtime_error("all your sbires should have a position");
		for (size_t i = 0; i < sbires.size(); i++)
		{
			_sbiresNames.push_back(sbires[i].asString());
			auto v = rtype::ecs::Vector3f(sbiresPos[3 * i].asFloat(),
				sbiresPos[3 * i + 1].asFloat(),
				sbiresPos[3 * i + 2].asFloat());
			_sbiresPos.push_back(v);
		}

	}
}

void FormationComponent::start()
{
	if (gameObject().isLocal())
	{
		auto t = gameObject().getComponent<ITransform>();
		if (!t)
			throw std::runtime_error("A formation must have a Transform");

		auto leader = gameEngine().createGameObject(_leaderName);

		auto leaderT = leader->getComponent<ITransform>();
		if (!leaderT)
			throw std::runtime_error("A formation leader must have a Transform");
		_leaderT = leaderT;
		leaderT->setPosition(_leaderPos);
		leaderT->setParent(t);

		auto itPos = _sbiresPos.begin();
		for (auto itNames = _sbiresNames.begin();
			 itNames != _sbiresNames.end() && itPos != _sbiresPos.end();
			 itNames++, itPos++)
		{
			auto sbire = gameEngine().createGameObject(*itNames);
			auto sbireT = sbire->getComponent<ITransform>();
			if (!sbireT)
				throw std::runtime_error("A formation sbire must have a Transform");
			sbireT->setPosition(*itPos);
			sbireT->setParent(leaderT);
		}
	}
}

void FormationComponent::update()
{
	if (!_leaderT.lock())
		gameObject().destroy();
}

void FormationComponent::draw()
{
}
