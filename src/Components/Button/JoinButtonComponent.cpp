#include <iostream>
#include <sstream>

#include "RType/ECS/GameEngine.hpp"
#include "Components/Button/JoinButtonComponent.hpp"
#include "Components/TextRenderer/ITextRenderer.hpp"

RTYPE_COMPONENT_IMPL(JoinButtonComponent)

void	JoinButtonComponent::update()
{
	if (this->isClicked())
	{
		auto	Ip = gameEngine().find("MenuIPText");
		auto	Port = gameEngine().find("MenuPortText");
		auto	IdRoom = gameEngine().find("MenuIdRoomText");

		if (Ip && Port && IdRoom)
		{
			auto		IpRenderer = Ip->getComponent<ITextRenderer>();
			auto		PortRenderer = Port->getComponent<ITextRenderer>();
			auto		IdRoomRenderer = IdRoom->getComponent<ITextRenderer>();

			if (IpRenderer && PortRenderer && IdRoomRenderer)
			{
				std::string		ip = IpRenderer->getText();
				std::string		portString = PortRenderer->getText();
				std::string		idString = IdRoomRenderer->getText();

				uint16_t port;
				uint32_t id;

				{
					std::istringstream iss(portString);
					iss >> port;
				}

				{
					std::istringstream iss(idString);
					iss >> id;
				}

				if (port > 0 && id > 0)
				{
					gameEngine().loadScene("MultiPlayerScene");
					gameEngine().getNetwork().connect(ip, port, id);
				}
			}
		}
	}
	AbstractButton::update();
}
