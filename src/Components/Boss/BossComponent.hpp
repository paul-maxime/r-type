#ifndef BOSSCOMPONENT_HPP_
#define BOSSCOMPONENT_HPP_

#include <vector>

#include "RType/ECS/AComponent.hpp"
#include "Components/Behavior/IBehavior.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/Animations/IAnimations.hpp"
#include "Components/ShootableEnemy/IShootableEnemy.hpp"
#include "Components/ColliderSystem/ICollider.hpp"
#include "Components/SpriteRenderer/ISpriteRenderer.hpp"

RTYPE_PLUGIN
class BossComponent : public rtype::ecs::AComponent
{
	RTYPE_COMPONENT

private:
	rtype::ecs::Vector2f _vScrollingSpeed;
	std::vector<std::function<bool (ITransform & t,
					IBehavior &,
					IAnimations &)>> _pattern;
	int16_t _baseLife;
	size_t _patternPlaying;
	bool _patternInit;
	float _patternCd;
	uint8_t _stade;
	std::string _spritep1;
	std::string _spritep2;

	bool _destroy;
	size_t _explosions;

	virtual void checkDepencies(std::shared_ptr<ITransform> const & t,
		std::shared_ptr<IBehavior> const & b,
		std::shared_ptr<IAnimations> const & a,
		std::shared_ptr<IShootableEnemy> const & s) const;
	virtual bool startPattern(ITransform& t,
		IBehavior& b, IAnimations& a);
	virtual bool openPattern(ITransform & t,
		IBehavior & b, IAnimations & a);
	virtual bool closePattern(ITransform & t,
		IBehavior & b, IAnimations & a);
	virtual bool scrollingPattern(ITransform & t,
		IBehavior & b, IAnimations & a);
	virtual void launchMinions(ITransform & t, IAnimations & a);
	virtual void launchMinion(ITransform & t, float y, float speedY);
	virtual bool laserPattern(ITransform &,
		IBehavior &, IAnimations & a);
	virtual bool destroyPattern(ITransform &,
		IBehavior &, IAnimations & a);

	virtual void explosion(ITransform& t);

public:
	virtual ~BossComponent() {}

	virtual void start();
	virtual void update();
	virtual void loadFile(rtype::ecs::file::Value const& file);
	virtual void serialize(rtype::system::BinaryWriter& writer);
	virtual void unserialize(rtype::system::BinaryReader& reader);
};

#endif // !BOSSCOMPONENT_HPP_
