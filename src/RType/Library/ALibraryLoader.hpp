#ifndef RTYPE_LIBRARY_ALIBRARYLOADER_HPP_
#define RTYPE_LIBRARY_ALIBRARYLOADER_HPP_

#include <stdexcept>

#include "RType/System/NonCopyable.hpp"
#include "RType/Library/IPlugin.hpp"

namespace rtype
{
	namespace library
	{
		class ALibraryLoader : public system::NonCopyable
		{
		public:
			virtual ~ALibraryLoader() {}

			template<typename T>
			T* instantiate() const
			{
				T* instance = dynamic_cast<T*>(getPlugin());
				if (!instance)
					throw std::logic_error("Could not cast a plugin into another type.");
				return instance;
			}

		protected:
			typedef IPlugin* (*InstantiateFct)();

			virtual IPlugin* getPlugin() const = 0;
		};
	} // namespace library
} // namespace rtype

#endif // RTYPE_LIBRARY_ALIBRARYLOADER_HPP_
