#include <iostream>
#include <thread>
#include <chrono>
#include "RType/Client/AssetsManager.hpp"
#include "RType/Client/SfmlAudioEngine.hpp"

int main()
{
	rtype::client::AssetsManager* assets = new rtype::client::AssetsManager("assets");
	rtype::ecs::IAudioEngine* audio = new rtype::client::SfmlAudioEngine(*assets);

	std::cout << "Testing normal explosion..." << std::endl;
	audio->playSound("sounds/test-explosion.wav");
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Testing spacialized explosion (left)..." << std::endl;
	audio->playSound("sounds/test-explosion.wav", 100.0f,
		rtype::ecs::Vector3f(-5.0f, 0.0f, 0.0f), 5.0f, 0.0f);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Testing spacialized explosion (right)..." << std::endl;
	audio->playSound("sounds/test-explosion.wav", 100.0f,
		rtype::ecs::Vector3f(5.0f, 0.0f, 0.0f), 5.0f, 0.0f);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Testing spacialized explosion (behind)..." << std::endl;
	audio->playSound("sounds/test-explosion.wav",100.0f,
		rtype::ecs::Vector3f(0.0f, -5.0f, 0.0f), 5.0f, 0.0f);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Testing far spacialized attenued explosion (left)..." << std::endl;
	audio->playSound("sounds/test-explosion.wav",100.0f,
		rtype::ecs::Vector3f(-30.0f, 0.0f, 0.0f), 5.0f, 5.0f);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Testing far spacialized attenued explosion (right)..." << std::endl;
	audio->playSound("sounds/test-explosion.wav",100.0f,
		rtype::ecs::Vector3f(30.0f, 0.0f, 0.0f), 5.0f, 5.0f);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "* Moving listener to the left and reducing volume..." << std::endl;
	audio->setListener(rtype::ecs::Vector3f(-5.0f, 0.0f, 0.0f),
		rtype::ecs::Vector3f());
	audio->setVolume(30.0f);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "Testing spacialized explosion (left)..." << std::endl;
	audio->playSound("sounds/test-explosion.wav",100.0f,
		rtype::ecs::Vector3f(-5.0f, 0.0f, 0.0f), 5.0f, 0.0f);
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Testing a lot of normal explosions..." << std::endl;
	audio->playSound("sounds/test-explosion.wav");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	audio->playSound("sounds/test-explosion.wav");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	audio->playSound("sounds/test-explosion.wav");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	audio->playSound("sounds/test-explosion.wav");
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "* Reseting the volume..." << std::endl;
	audio->setVolume(100.0f);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "Testing music..." << std::endl;
	audio->playMusic("musics/harp.ogg");
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "Reseting music..." << std::endl;
	audio->playMusic("musics/harp.ogg");
	std::this_thread::sleep_for(std::chrono::seconds(10));

	std::cout << "* Alright, we're done!" << std::endl;
}
