#ifndef RTYPE_NETWORK_UDPSOCKET_HPP_
#define RTYPE_NETWORK_UDPSOCKET_HPP_

#ifdef RTYPE_IS_UNIX

# include "LinuxUdpSocket.hpp"

namespace rtype
{
	namespace network
	{
		typedef LinuxUdpSocket UdpSocket;
	}
}

#elif RTYPE_IS_WIN32

# include "WindowsUdpSocket.hpp"

namespace rtype
{
	namespace network
	{
		typedef WindowsUdpSocket UdpSocket;
	}
}

#else
# error operating system not supported (UdpSocket)
#endif

#endif // RTYPE_NETWORK_UDPSOCKET_HPP_
