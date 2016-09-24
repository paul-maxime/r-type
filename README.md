# R-Type Project #

This is a small project (2 months) we did for our school in 2014.

The project is called R-Type, as an homage for the 1987 video game.

YouTube video: https://www.youtube.com/watch?v=OkzBluc3uvA

## Branches: ##

+ master: Contains a stable and numbered version of the project.
  Only working and fully-tested versions may be merged into master.

+ develop: Main working branch.
  Every new feature or bug fix should be merged into develop.

## How does the Network work? ##

We have only one udp packet: UpdateEntities.

UpdateEntities is sent between the server and the client and contains entities to update.
This packet is sent at a regular interval (to be defined, like 50-200ms).
The client is only allowed to update a few entities, like the inputs. The server will check that.

### How is this possible ? How do we join and quit a room ?

When the server receives the Update packet from an unknown sender, it adds the player to the room.

When the server doesn't receive the Update packets for 5 seconds, it disconnects the player.

The room id is stored into the UpdateEntities packet, you can join the id you want.

### How do I use the RFC ###

The RFC is currently in xml format. You can find the last version in the branch *conception*. To compile it to another format (including txt/html/pdf), use [http://xml.resource.org](xml.resource.org).

## How does the ECS work? ##

Our _Entity Component System_ is a simplified version of Unity's.

+ The program core will load every component and every entity.

+ The program core will execute every component of every entity at each frame.

+ Components are loaded from dynamic libraries (.so, .dll).

+ Components contain variables and functions.

+ Components may overload update() and draw() functions.

+ An entity is a json-like file and contains a list of components.

### Entity example (BossEnnemy.json)
```json
    {
	  "SpriteComponent" :
	  {
	    "x" : 0,
	    "y" : 0,
	    "image" : "assets/boss.png"
	  },
	  "MovementComponent" : "wave",
	  "MissileSpawnComponent" :
	  {
	    "type" : "BossMissile",
	    "minInterval" : 400,
	    "maxInterval" : 800
	  },
	  "LifeComponent" :
	  {
	    "life" : 1000
	  }
	}
```
_This is an example and not a valid entity._

### Component example (SpriteComponent.cpp)
```c++
	  class SpriteComponent : public Component
	  {
	    public:
	      int x;
	      int y;
	      std::string image;

	      virtual void update()
	      {
	        // Empty, that function may be deleted.
	        // We may use the 'isLocal' boolean here.
	      }
	      virtual void draw()
	      {
	        // Will only be called client-side.
	        GraphicsEngine::draw(image, x, y);
	      }
	      virtual void serialize(Output& output)
	      {
	        // Will only be called server-side.
	        output << x << y;
	      }
	      virtual void unserialize(Input& input)
	      {
	        // Will only be called client-side.
	        // Note: we should extrapolate the values here in order to smooth the movement.
	       input >> x >> y;
	      }
	  };
```
_Again, this is a short example and not a working code._

## Contributors: ##

* Jean Fauquenot
* Maxime Laffaire
* Nicolas Vareille
* Paul-Maxime Le Duc
* Thibault Duval
