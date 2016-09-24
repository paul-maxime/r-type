#ifndef GRAVITATIONFORCE_HPP_
# define GRAVITATIONFORCE_HPP_

# include "RType/ECS/AComponent.hpp"
# include "Components/ColliderSystem/ICollision.hpp"
# include "Components/Transform/ITransform.hpp"
# include "Components/Force/AForce.hpp"
# include "Components/PlayerShip/IPlayerShip.hpp"
# include "Components/BulletComponent/IBullet.hpp"
# include "RType/ECS/GameEngine.hpp"

RTYPE_PLUGIN
class GravitationForce : public rtype::ecs::AComponent, public ICollision, public AForce
{
	RTYPE_COMPONENT

private:
	float _y;

public:
	GravitationForce();
	virtual ~GravitationForce();

	virtual void loadFile(const rtype::ecs::file::Value&);
	virtual void start();
	virtual void update();
	virtual void onCollision(rtype::ecs::GameObject &);
	virtual size_t getInstanceId();
	virtual void release();
public:
	std::vector<std::string> _weapons;
	std::string _weapon;
	float _cooldown;
};

#endif
