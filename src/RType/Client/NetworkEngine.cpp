#include "RType/Client/NetworkEngine.hpp"

namespace rtype
{
	namespace client
	{
		NetworkEngine::NetworkEngine()
			: _isConnected(false),
			  _isConnecting(false)
		{
		}

		void NetworkEngine::connect(const std::string& host, uint16_t port, uint32_t gameId)
		{
			_isConnected = false;
			_isConnecting = true;
			_host = host;
			_port = port;
			_gameId = gameId;
		}

		void NetworkEngine::disconnect()
		{
			_isConnected = false;
			_isConnecting = false;
		}

		bool NetworkEngine::isConnected() const
		{
			return _isConnected;
		}

		bool NetworkEngine::isConnecting() const
		{
			return _isConnecting;
		}

		void NetworkEngine::setConnected()
		{
			_isConnected = true;
			_isConnecting = false;
		}

		const std::string& NetworkEngine::host() const
		{
			return _host;
		}

		uint16_t NetworkEngine::port() const
		{
			return _port;
		}

		uint32_t NetworkEngine::gameId() const
		{
			return _gameId;
		}
	}
}
