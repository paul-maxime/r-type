#include "RType/Client/AssetError.hpp"

namespace rtype
{
	namespace client
	{
		AssetError::AssetError(const std::string& message)
			: runtime_error(message)
		{
		}

		AssetError::~AssetError() throw()
		{
		}
	} // namespace client
} // namespace rtype
