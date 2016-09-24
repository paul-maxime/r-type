#ifndef RTYPE_CLIENT_ASSETERROR_HPP_
#define RTYPE_CLIENT_ASSETERROR_HPP_

#include <stdexcept>
#include <string>

namespace rtype
{
	namespace client
	{
		class AssetError : public std::runtime_error
		{
		public:
			AssetError(const std::string& message);
			virtual ~AssetError() throw();
		};
	} // namespace client
} // namespace rtype

#endif // RTYPE_CLIENT_ASSETERROR_HPP_
