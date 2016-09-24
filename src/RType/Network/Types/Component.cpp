#include "RType/Network/Types/Component.hpp"

namespace rtype
{
	namespace network
	{
		namespace types
		{
			const std::string& Component::type() const
			{
				return _type;
			}

			void Component::type(const std::string& value)
			{
				_type = value;
			}

			const std::string& Component::data() const
			{
				return _data;
			}

			void Component::data(const std::string& value)
			{
				_data = value;
			}

			void Component::serialize(system::BinaryWriter& writer) const
			{
				writer << _type << _data;
			}

			void Component::unserialize(system::BinaryReader& reader)
			{
				reader >> _type >> _data;
			}
		} // namespace types
	} // namespace network
} // namespace rtype
