# ---------------------------------- #
#				     #
#		R-TYPE		     #
#				     #
# ---------------------------------- #

cmake_minimum_required(VERSION 2.8)
project(RType)

#################
# SOURCES FILES #
#################

set(SHARED_SRC
  src/RType/System/Chrono.hpp
  src/RType/System/Random.cpp
  src/RType/System/Random.hpp
  src/RType/System/NonCopyable.hpp
  src/RType/System/BinaryReader.cpp
  src/RType/System/BinaryReader.hpp
  src/RType/System/BinaryWriter.cpp
  src/RType/System/BinaryWriter.hpp
  src/RType/System/EndOfStreamError.cpp
  src/RType/System/EndOfStreamError.hpp
  src/RType/Network/IUdpSocket.hpp
  src/RType/Network/UdpSocket.hpp
  src/RType/Network/SocketError.cpp
  src/RType/Network/SocketError.hpp
  src/RType/Network/PacketFactory.cpp
  src/RType/Network/PacketFactory.hpp
  src/RType/Network/PacketReceiver.cpp
  src/RType/Network/PacketReceiver.hpp
  src/RType/Network/PacketSender.cpp
  src/RType/Network/PacketSender.hpp
  src/RType/Network/Packets/APacket.cpp
  src/RType/Network/Packets/APacket.hpp
  src/RType/Network/Packets/UpdateEntities.cpp
  src/RType/Network/Packets/UpdateEntities.hpp
  src/RType/Network/Types/Component.cpp
  src/RType/Network/Types/Component.hpp
  src/RType/Network/Types/Entity.cpp
  src/RType/Network/Types/Entity.hpp
  src/RType/Library/ALibraryLoader.hpp
  src/RType/Library/LibraryLoader.hpp
  src/RType/Library/IPlugin.hpp
  src/RType/Library/LibraryError.cpp
  src/RType/Library/LibraryError.hpp
  src/RType/Library/LibraryManager.cpp
  src/RType/Library/LibraryManager.hpp
  src/RType/ECS/IGraphicsEngine.hpp
  src/RType/ECS/IAudioEngine.hpp
  src/RType/ECS/INetworkEngine.hpp
  src/RType/ECS/AComponent.hpp
  src/RType/ECS/GameEngine.cpp
  src/RType/ECS/GameEngine.hpp
  src/RType/ECS/GameObject.cpp
  src/RType/ECS/GameObject.hpp
  src/RType/ECS/IInput.hpp
  src/RType/ECS/Vector2.hpp
  src/RType/ECS/Vector3.hpp
  src/RType/ECS/Rect.hpp
  src/RType/ECS/File/Loader.cpp
  src/RType/ECS/File/Loader.hpp
  src/RType/ECS/File/Value.cpp
  src/RType/ECS/File/Value.hpp
  )

set(UNIX_SRC
  src/RType/Network/LinuxUdpSocket.cpp
  src/RType/Network/LinuxUdpSocket.hpp
  src/RType/Library/LinuxLibraryLoader.cpp
  src/RType/Library/LinuxLibraryLoader.hpp
  )

set(WIN32_SRC
  src/RType/Network/WindowsUdpSocket.cpp
  src/RType/Network/WindowsUdpSocket.hpp
  src/RType/Library/WindowsLibraryLoader.cpp
  src/RType/Library/WindowsLibraryLoader.hpp
  )

set(CLIENT_SRC
  src/RType/Client/Client.cpp
  src/RType/Client/Client.hpp
  src/RType/Client/AssetsManager.cpp
  src/RType/Client/AssetsManager.hpp
  src/RType/Client/AssetError.cpp
  src/RType/Client/AssetError.hpp
  src/RType/Client/SfmlGraphicsEngine.cpp
  src/RType/Client/SfmlGraphicsEngine.hpp
  src/RType/Client/SfmlAudioEngine.cpp
  src/RType/Client/SfmlAudioEngine.hpp
  src/RType/Client/SFMLInput.cpp
  src/RType/Client/SFMLInput.hpp
  src/RType/Client/NetworkEngine.cpp
  src/RType/Client/NetworkEngine.hpp
  )

set(SERVER_SRC
  src/RType/Server/main.cpp
  src/RType/Server/Server.cpp
  src/RType/Server/Server.hpp
  src/RType/Server/RoomManager.cpp
  src/RType/Server/RoomManager.hpp
  src/RType/Server/Room.cpp
  src/RType/Server/Room.hpp
  src/RType/Server/User.cpp
  src/RType/Server/User.hpp
  src/RType/Server/ThreadPool.cpp
  src/RType/Server/ThreadPool.hpp
  src/RType/Server/AsyncUdpServer.cpp
  src/RType/Server/AsyncUdpServer.hpp
  )

#########################
# GENERAL CONFIGURATION #
#########################

# output in bin/ directory

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
if (MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)
endif()

# enable c++11 and warnings on unix

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")
endif()

# include the src/ directory

include_directories(src/)
include_directories(src/jsoncpp/include/)

# define the windows and linux macros and include valid files

if (UNIX)
  add_definitions(-DRTYPE_IS_UNIX)
  set(SHARED_SRC ${SHARED_SRC} ${UNIX_SRC})
else()
  add_definitions(-DRTYPE_IS_WIN32)
  set(SHARED_SRC ${SHARED_SRC} ${WIN32_SRC})
endif()

# import static json library

if (UNIX)
  set(JSON_LIBRARY_FILE ${PROJECT_SOURCE_DIR}/lib/libjsoncpp_linux_x86_64.a)
else()
  set(JSON_LIBRARY_FILE ${PROJECT_SOURCE_DIR}/lib/jsoncpp_windows_x86.lib)
  set(JSON_LIBRARY_FILE_DEBUG ${PROJECT_SOURCE_DIR}/lib/jsoncpp_windows_x86_DEBUG.lib)
endif()

add_library(json_lib STATIC IMPORTED)
set_property(TARGET json_lib PROPERTY IMPORTED_LOCATION ${JSON_LIBRARY_FILE})

if (WIN32)
  add_library(json_lib_debug STATIC IMPORTED)
  set_property(TARGET json_lib_debug PROPERTY IMPORTED_LOCATION ${JSON_LIBRARY_FILE_DEBUG})
endif()

if (UNIX)
  set(JSON_LIBRARY json_lib)
else()
  set(JSON_LIBRARY
    debug json_lib_debug
	optimized json_lib
  )
endif()

# set correct sfml library for debug and release

if (UNIX)
  set(SFML_LIBRARIES sfml-system sfml-window sfml-graphics sfml-audio)
else()
  set(SFML_LIBRARIES
    debug sfml-system-d debug sfml-window-d debug sfml-graphics-d debug sfml-audio-d
    optimized sfml-system optimized sfml-window optimized sfml-graphics optimized sfml-audio
    )
  set(SFML_LIBRARIES ${SFML_LIBRARIES} sfml-main)
endif()

# find sfml on windows

if (WIN32)
  set(SFML_INCLUDE_PATH "NOTFOUND" CACHE PATH "SFML include directory")
  set(SFML_LIBRARY_PATH "NOTFOUND" CACHE PATH "SFML library directory")

  if (NOT SFML_INCLUDE_PATH OR NOT SFML_LIBRARY_PATH)
    message(FATAL_ERROR "Please configure SFML path before continuing.")
  endif()

  include_directories(${SFML_INCLUDE_PATH})
  link_directories(${SFML_LIBRARY_PATH})
endif()

# plugins configuration macro

macro(rtype_plugin name)
  set_target_properties(${name} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugins)
  if (WIN32)
    target_link_libraries(${name} shared ${JSON_LIBRARY})
  endif()
  if (MSVC)
    set_target_properties(${name} PROPERTIES
      LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/plugins)
    set_target_properties(${name} PROPERTIES
      LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/plugins)
  endif()
endmacro()

#########################
# SHARED STATIC LIBRARY #
#########################

add_library(shared STATIC ${SHARED_SRC})
set_target_properties(shared PROPERTIES POSITION_INDEPENDENT_CODE ON)

#########################
# CLIENT STATIC LIBRARY #
#########################

add_library(client STATIC ${CLIENT_SRC})

#########################
# SERVER STATIC LIBRARY #
#########################

add_library(server STATIC ${SERVER_SRC})

##############
# COMPONENTS #
##############

add_library(Transform MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/Transform/Transform.hpp
  src/Components/Transform/Transform.cpp
  )
rtype_plugin(Transform)

add_library(HelloWorld MODULE
  src/Components/HelloWorld/HelloWorldComponent.hpp
  src/Components/HelloWorld/HelloWorldComponent.cpp
  )
rtype_plugin(HelloWorld)

add_library(Shader MODULE
  src/Components/Shader/ShaderComponent.hpp
  src/Components/Shader/ShaderComponent.cpp
  )
rtype_plugin(Shader)

add_library(PixelShader MODULE
  src/Components/PixelShader/PixelShaderComponent.hpp
  src/Components/PixelShader/PixelShaderComponent.cpp
  )
rtype_plugin(PixelShader)

add_library(GlobalPixelShader MODULE
  src/Components/GlobalPixelShader/GlobalPixelShaderComponent.hpp
  src/Components/GlobalPixelShader/GlobalPixelShaderComponent.cpp
  )
rtype_plugin(GlobalPixelShader)

add_library(GlobalBlinkShader MODULE
  src/Components/GlobalBlinkShader/GlobalBlinkShaderComponent.hpp
  src/Components/GlobalBlinkShader/GlobalBlinkShaderComponent.cpp
  )
rtype_plugin(GlobalBlinkShader)

add_library(WaveShader MODULE
  src/Components/WaveShader/WaveShaderComponent.hpp
  src/Components/WaveShader/WaveShaderComponent.cpp
  )
rtype_plugin(WaveShader)

add_library(Button MODULE
  src/Components/Button/AbstractButton.hpp
  src/Components/Button/AbstractButton.cpp
  src/Components/Button/ButtonComponent.hpp
  src/Components/Button/ButtonComponent.cpp
  )
rtype_plugin(Button)

add_library(JoinButton MODULE
  src/Components/Button/AbstractButton.hpp
  src/Components/Button/AbstractButton.cpp
  src/Components/Button/JoinButtonComponent.hpp
  src/Components/Button/JoinButtonComponent.cpp
  )
rtype_plugin(JoinButton)

add_library(OnePlayerButton MODULE
  src/Components/Button/AbstractButton.hpp
  src/Components/Button/AbstractButton.cpp
  src/Components/Button/OnePlayerButtonComponent.hpp
  src/Components/Button/OnePlayerButtonComponent.cpp
  )
rtype_plugin(OnePlayerButton)

add_library(VolumeModifier MODULE
  src/Components/VolumeModifier/VolumeModifierComponent.hpp
  src/Components/VolumeModifier/VolumeModifierComponent.cpp
  )
rtype_plugin(VolumeModifier)

add_library(Menu MODULE
  src/Components/Menu/MenuComponent.hpp
  src/Components/Menu/MenuComponent.cpp
  )
rtype_plugin(Menu)

add_library(KonamiCode MODULE
  src/Components/KonamiCode/KonamiCodeComponent.hpp
  src/Components/KonamiCode/KonamiCodeComponent.cpp
  )
rtype_plugin(KonamiCode)

add_library(WindowHandler MODULE
  src/Components/WindowHandler/WindowHandlerComponent.hpp
  src/Components/WindowHandler/WindowHandlerComponent.cpp
  )
rtype_plugin(WindowHandler)

add_library(Background MODULE
  src/Components/Background/BackgroundComponent.hpp
  src/Components/Background/BackgroundComponent.cpp
  )
rtype_plugin(Background)

add_library(Animations MODULE
  src/Components/SpriteRenderer/ISpriteRenderer.hpp
  src/Components/Animations/IAnimations.hpp
  src/Components/Animations/AnimationsComponent.hpp
  src/Components/Animations/AnimationsComponent.cpp
  )
rtype_plugin(Animations)

add_library(SpriteRenderer MODULE
  src/Components/SpriteRenderer/ISpriteRenderer.hpp
  src/Components/SpriteRenderer/SpriteRendererComponent.hpp
  src/Components/SpriteRenderer/SpriteRendererComponent.cpp
  )
rtype_plugin(SpriteRenderer)

add_library(Collider MODULE
  src/Components/Collider/Collider.hpp
  src/Components/Collider/Collider.cpp
  )
rtype_plugin(Collider)

add_library(Behavior MODULE
  src/Components/Behavior/IBehavior.hpp
  src/Components/Behavior/BehaviorComponent.hpp
  src/Components/Behavior/BehaviorComponent.cpp
  )
rtype_plugin(Behavior)

add_library(Attack MODULE
  src/Components/Weapons/BulletSpawner/BulletSpawner.cpp
  src/Components/Weapons/BulletSpawner/BulletSpawner.hpp
  src/Components/Attack/AttackComponent.hpp
  src/Components/Attack/AttackComponent.cpp
  )
rtype_plugin(Attack)

add_library(Scene MODULE
  src/Components/Scene/SceneComponent.hpp
  src/Components/Scene/SceneComponent.cpp
  )
rtype_plugin(Scene)

add_library(ParentDependent MODULE
  src/Components/ParentDependent/ParentDependentComponent.hpp
  src/Components/ParentDependent/ParentDependentComponent.cpp
  )
rtype_plugin(ParentDependent)

add_library(PlayerInputs MODULE
  src/Components/PlayerInputs/IPlayerInputs.hpp
  src/Components/PlayerInputs/PlayerInputsComponent.hpp
  src/Components/PlayerInputs/PlayerInputsComponent.cpp
  )
rtype_plugin(PlayerInputs)

add_library(WeaponsHolder MODULE
  src/Components/PlayerShip/IPlayerShip.hpp
  src/Components/Weapons/WeaponsHolder/IWeaponsHolder.hpp
  src/Components/Weapons/WeaponsHolder/WeaponsHolderComponent.hpp
  src/Components/Weapons/WeaponsHolder/WeaponsHolderComponent.cpp
  )
rtype_plugin(WeaponsHolder)

add_library(Weapons MODULE
  src/Components/Weapons/BulletSpawner/BulletSpawner.hpp
  src/Components/Weapons/BulletSpawner/BulletSpawner.cpp
  src/Components/Weapons/Weapons/IWeapons.hpp
  src/Components/Weapons/Weapons/WeaponsComponent.hpp
  src/Components/Weapons/Weapons/WeaponsComponent.cpp
  )
rtype_plugin(Weapons)

add_library(MomsKnife MODULE
  src/Components/Weapons/Weapons/IWeapons.hpp
  src/Components/Weapons/MomsKnife/MomsKnifeComponent.hpp
  src/Components/Weapons/MomsKnife/MomsKnifeComponent.cpp
  )
rtype_plugin(MomsKnife)

add_library(FadeOut MODULE
  src/Components/FadeOut/IFadeOut.hpp
  src/Components/FadeOut/FadeOutComponent.hpp
  src/Components/FadeOut/FadeOutComponent.cpp
  )
rtype_plugin(FadeOut)

add_library(Player MODULE
  src/Components/Player/IPlayerComponent.hpp
  src/Components/Player/PlayerComponent.hpp
  src/Components/Player/PlayerComponent.cpp
  )
rtype_plugin(Player)

add_library(DestroyEvent MODULE
  src/Components/DestroyEvent/DestroyEventComponent.hpp
  src/Components/DestroyEvent/DestroyEventComponent.cpp
  )
rtype_plugin(DestroyEvent)

add_library(PlayerController MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/PlayerInputs/IPlayerInputs.hpp
  src/Components/PlayerController/PlayerControllerComponent.hpp
  src/Components/PlayerController/PlayerControllerComponent.cpp
  )
rtype_plugin(PlayerController)

add_library(SelfDestruction MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/SelfDestruction/SelfDestructionComponent.hpp
  src/Components/SelfDestruction/SelfDestructionComponent.cpp
  )
rtype_plugin(SelfDestruction)

add_library(AudioListener MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/AudioListener/AudioListenerComponent.hpp
  src/Components/AudioListener/AudioListenerComponent.cpp
  )
rtype_plugin(AudioListener)

add_library(AudioSource MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/AudioSource/IAudioSource.hpp
  src/Components/AudioSource/AudioSourceComponent.hpp
  src/Components/AudioSource/AudioSourceComponent.cpp
  )
rtype_plugin(AudioSource)

add_library(SoundPlayer MODULE
  src/Components/AudioSource/IAudioSource.hpp
  src/Components/SoundPlayer/SoundPlayerComponent.hpp
  src/Components/SoundPlayer/SoundPlayerComponent.cpp
  )
rtype_plugin(SoundPlayer)

add_library(MusicPlayer MODULE
  src/Components/MusicPlayer/MusicPlayerComponent.hpp
  src/Components/MusicPlayer/MusicPlayerComponent.cpp
  )
rtype_plugin(MusicPlayer)

add_library(ColliderSystem MODULE
  src/Components/ColliderSystem/ICollider.hpp
  src/Components/ColliderSystem/ICollision.hpp
  src/Components/ColliderSystem/IColliderSystem.hpp
  src/Components/ColliderSystem/ColliderSystem.hpp
  src/Components/ColliderSystem/ColliderSystem.cpp
  )
rtype_plugin(ColliderSystem)

add_library(TextRenderer MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/TextRenderer/TextRendererComponent.hpp
  src/Components/TextRenderer/TextRendererComponent.cpp
  )
rtype_plugin(TextRenderer)

add_library(TextInput MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/TextInput/TextInputComponent.hpp
  src/Components/TextInput/TextInputComponent.cpp
  )
rtype_plugin(TextInput)

add_library(EnnemyCollision MODULE
  src/Components/EnnemyCollision/EnnemyCollision.hpp
  src/Components/EnnemyCollision/EnnemyCollision.cpp
  )
rtype_plugin(EnnemyCollision)

add_library(Layer MODULE
  src/Components/Layer/LayerComponent.hpp
  src/Components/Layer/LayerComponent.cpp
  )
rtype_plugin(Layer)

add_library(HealBonus MODULE
  src/Components/HealBonus/HealBonus.hpp
  src/Components/HealBonus/HealBonus.cpp
  )
rtype_plugin(HealBonus)

add_library(SpeedBonus MODULE
  src/Components/SpeedBonus/SpeedBonus.hpp
  src/Components/SpeedBonus/SpeedBonus.cpp
  )
rtype_plugin(SpeedBonus)

add_library(WeaponBonus MODULE
  src/Components/WeaponBonus/WeaponBonus.hpp
  src/Components/WeaponBonus/WeaponBonus.cpp
  )
rtype_plugin(WeaponBonus)

add_library(ShootableEnemy MODULE
  src/Components/ShootableEnemy/IShootableEnemy.hpp
  src/Components/ShootableEnemy/ShootableEnemy.hpp
  src/Components/ShootableEnemy/ShootableEnemy.cpp
  )
rtype_plugin(ShootableEnemy)

add_library(LaserCollider MODULE
  src/Components/LaserCollider/LaserColliderComponent.hpp
  src/Components/LaserCollider/LaserColliderComponent.cpp
  )
rtype_plugin(LaserCollider)

add_library(Bullet MODULE
  src/Components/BulletComponent/IBullet.hpp
  src/Components/BulletComponent/BulletComponent.hpp
  src/Components/BulletComponent/BulletComponent.cpp
  )
rtype_plugin(Bullet)

add_library(Stage MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/Behavior/IBehavior.hpp
  src/Components/DestroyEvent/IDestroyEvent.hpp
  src/Components/Stage/IStage.hpp
  src/Components/Stage/StageComponent.hpp
  src/Components/Stage/StageComponent.cpp
  )
rtype_plugin(Stage)

add_library(StageName MODULE
  src/Components/TextRenderer/ITextRenderer.hpp
  src/Components/Stage/IStage.hpp
  src/Components/StageName/StageNameComponent.hpp
  src/Components/StageName/StageNameComponent.cpp
  )
rtype_plugin(StageName)

add_library(AnimationDeleter MODULE
  src/Components/AnimationDeleter/AnimationDeleterComponent.hpp
  src/Components/AnimationDeleter/AnimationDeleterComponent.cpp
  )
rtype_plugin(AnimationDeleter)

add_library(Formation MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/Formation/FormationComponent.hpp
  src/Components/Formation/FormationComponent.cpp
  )
rtype_plugin(Formation)

add_library(PlayerColorize MODULE
  src/Components/PlayerColorize/PlayerColorizeComponent.hpp
  src/Components/PlayerColorize/PlayerColorizeComponent.cpp
  )
rtype_plugin(PlayerColorize)

add_library(Boss MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/Boss/BossComponent.hpp
  src/Components/Boss/BossComponent.cpp
  )
rtype_plugin(Boss)

add_library(QueenFly MODULE
  src/Components/Weapons/BulletSpawner/BulletSpawner.hpp
  src/Components/Weapons/BulletSpawner/BulletSpawner.cpp
  src/Components/QueenFly/QueenFlyComponent.hpp
  src/Components/QueenFly/QueenFlyComponent.cpp
  )
rtype_plugin(QueenFly)

add_library(LaserBoss MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/LaserBoss/LaserBossComponent.hpp
  src/Components/LaserBoss/LaserBossComponent.cpp
  )
rtype_plugin(LaserBoss)

add_library(PlayerShip MODULE
  src/Components/PlayerShip/IPlayerShip.hpp
  src/Components/PlayerShip/PlayerShipComponent.hpp
  src/Components/PlayerShip/PlayerShipComponent.cpp
  )
rtype_plugin(PlayerShip)

add_library(Score MODULE
  src/Components/TextRenderer/ITextRenderer.hpp
  src/Components/Score/IScore.hpp
  src/Components/Score/ScoreComponent.hpp
  src/Components/Score/ScoreComponent.cpp
  )
rtype_plugin(Score)

add_library(TimeHUD MODULE
  src/Components/TextRenderer/ITextRenderer.hpp
  src/Components/TimeHUD/TimeHUDComponent.hpp
  src/Components/TimeHUD/TimeHUDComponent.cpp
  )
rtype_plugin(TimeHUD)

add_library(GravitationForce MODULE
  src/Components/Force/AForce.hpp
  src/Components/GravitationForce/GravitationForce.hpp
  src/Components/GravitationForce/GravitationForce.cpp
  )
rtype_plugin(GravitationForce)

add_library(Asteroid MODULE
  src/Components/SpriteRenderer/ISpriteRenderer.hpp
  src/Components/Asteroid/IAsteroid.hpp
  src/Components/Asteroid/AsteroidComponent.hpp
  src/Components/Asteroid/AsteroidComponent.cpp
  )
rtype_plugin(Asteroid)

add_library(AsteroidSpawner MODULE
  src/Components/AsteroidSpawner/AsteroidSpawnerComponent.hpp
  src/Components/AsteroidSpawner/AsteroidSpawnerComponent.cpp
  )
rtype_plugin(AsteroidSpawner)

add_library(Explosive MODULE
  src/Components/Transform/ITransform.hpp
  src/Components/Explosive/ExplosiveComponent.hpp
  src/Components/Explosive/ExplosiveComponent.cpp
  )
rtype_plugin(Explosive)

##########
# CLIENT #
##########

add_executable(RTypeClient
  WIN32
  src/RType/Client/main.cpp
  )

target_link_libraries(RTypeClient client shared ${JSON_LIBRARY} ${SFML_LIBRARIES})
if (UNIX)
  target_link_libraries(RTypeClient dl)
endif()

##########
# SERVER #
##########

add_executable(RTypeServer
  src/RType/Server/main.cpp
  )

target_link_libraries(RTypeServer server shared ${JSON_LIBRARY})
if (UNIX)
  target_link_libraries(RTypeServer pthread dl)
endif()

######################
# NETWORK TEST FILES #
######################

add_executable(test_udp_server src/tests/UdpServer.cpp)
target_link_libraries(test_udp_server shared ${JSON_LIBRARY})

add_executable(test_udp_client src/tests/UdpClient.cpp)
target_link_libraries(test_udp_client shared ${JSON_LIBRARY})

######################
# LIBRARY TEST FILES #
######################

add_library(emptyplugin MODULE
  src/tests/IHelloPlugin.hpp
  src/tests/EmptyPlugin.cpp
  src/tests/EmptyPlugin.hpp
  )

rtype_plugin(emptyplugin)

add_library(advancedplugin MODULE
  src/tests/IHelloPlugin.hpp
  src/tests/AdvancedPlugin.cpp
  src/tests/AdvancedPlugin.hpp
  )

rtype_plugin(advancedplugin)

add_executable(test_library
  src/tests/LibraryLoading.cpp
  src/tests/IHelloPlugin.hpp
  )

target_link_libraries(test_library shared)
if (UNIX)
  target_link_libraries(test_library dl)
endif()

#######################
# GRAPHICS TEST FILES #
#######################

add_executable(test_graphics
  WIN32
  src/tests/Graphics.cpp
  )
target_link_libraries(test_graphics client shared ${SFML_LIBRARIES})

#####################
# AUDIO TEST FILES #
#####################

add_executable(test_audio
  src/tests/Audio.cpp
  )
target_link_libraries(test_audio client shared ${SFML_LIBRARIES})

###################
# JSON TEST FILES #
###################

add_executable(test_json
  src/tests/TestJson.cpp
  src/RType/ECS/File/Loader.cpp)
target_link_libraries(test_json shared ${JSON_LIBRARY})

#########################
# THREADPOOL TEST FILES #
#########################

add_executable(test_threads
  src/tests/TestThreadPool.cpp)
target_link_libraries(test_threads server)
if (UNIX)
  target_link_libraries(test_threads pthread)
endif()

#####################
# BINARY TEST FILES #
#####################

add_executable(test_binary
  src/tests/TestBinaryStream.cpp)
target_link_libraries(test_binary shared)
