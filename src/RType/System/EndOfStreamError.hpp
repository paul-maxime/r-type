#ifndef RTYPE_SYSTEM_ENDOFSTREAMERROR_HPP_
#define RTYPE_SYSTEM_ENDOFSTREAMERROR_HPP_

#include <stdexcept>

namespace rtype
{
	namespace system
	{
		class EndOfStreamError : public std::runtime_error
		{
		public:
			EndOfStreamError();
			virtual ~EndOfStreamError() throw();
		};
	} // namespace system
} // namespace rType

#endif // RTYPE_SYSTEM_ENDOFSTREAMERROR_HPP_
