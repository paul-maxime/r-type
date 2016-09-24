#ifndef ATTACK_COMPONENT_HPP_
#define ATTACK_COMPONENT_HPP_

#include <functional>
#include <vector>
#include <unordered_map>

#include "Components/Weapons/BulletSpawner/BulletSpawner.hpp"
#include "RType/ECS/AComponent.hpp"
#include "RType/ECS/GameEngine.hpp"

RTYPE_PLUGIN
class AttackComponent : public rtype::ecs::AComponent, public BulletSpawner
{
	RTYPE_COMPONENT

private:
	struct Weapon
	{
		std::string atkAnim;
		std::string startAtkAnim;
		std::string stopAtkAnim;
		float playedAtk;
		float timer;
		std::vector< std::string > bullets;
		rtype::ecs::Vector2f offset;
		std::string type;
		std::vector< float > cooldown;
		unsigned int cdIdx;
		float bulletSpeed;
		float angle;
		float spread;
		int quantity;
		bool guided;
	};

	static const std::string DEFAULT_BULLET_TYPE;
	static const std::unordered_map< std::string, std::function<void (AttackComponent&, Weapon&)> > ATTACKS;

public:
	virtual ~AttackComponent() {}

	virtual void start();
	virtual void update();
	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void draw();

private:
	void parseWeapon(const rtype::ecs::file::Value&);

	void updateAim(Weapon&);

	void setupAtkAnim(Weapon&);
	void playAtkAnim(Weapon&);

	void shoot(Weapon&);
	void laser(Weapon&);

private:
	bool _debug;
	std::vector< Weapon > _weapons;
	unsigned int _idx;
};

#endif /* !ATTACK_COMPONENT_HPP_ */
