#ifndef MOMS_KNIFE_COMPONENT_HPP_
#define MOMS_KNIFE_COMPONENT_HPP_

#include <functional>
#include <unordered_map>
#include "Components/PlayerInputs/APlayerControllable.hpp"
#include "Components/Transform/ITransform.hpp"
#include "Components/Weapons/Weapons/IWeapons.hpp"
#include "Components/ColliderSystem/ICollision.hpp"
#include "RType/ECS/Vector3.hpp"
#include "RType/ECS/AComponent.hpp"

RTYPE_PLUGIN
class MomsKnifeComponent : public rtype::ecs::AComponent, public APlayerControllable, public IWeapons,
						   public ICollision
{
	RTYPE_COMPONENT

private:
	static const float MAX_LOAD;

public:
	virtual ~MomsKnifeComponent() {}

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void onCollision(rtype::ecs::GameObject &);

	virtual void upgrade() {};
	virtual void downgrade() {};
	virtual void addSpeed(float) {};
	virtual void addDamage(int8_t damage);
	virtual void addSpeed(int8_t);

private:
	void attacking(ITransform&);
	void loading();

private:
	rtype::ecs::Vector3f _offset;
	int8_t _damage;
	float _speed;
	bool _atkPressed;
	bool _attacking;
};

#endif /* !MOMS_KNIFE_COMPONENT_HPP_ */
