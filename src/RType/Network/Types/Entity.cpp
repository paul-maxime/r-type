#include <utility>

#include "RType/Network/Types/Entity.hpp"

namespace rtype
{
	namespace network
	{
		namespace types
		{
			uint32_t Entity::id() const
			{
				return _id;
			}

			void Entity::id(uint32_t value)
			{
				_id = value;
			}

			void Entity::name(const std::string& value)
			{
				_name = value;
			}

			const std::string& Entity::name() const
			{
				return _name;
			}

			void Entity::originalName(const std::string& value)
			{
				_originalName = value;
			}

			const std::string& Entity::originalName() const
			{
				return _originalName;
			}

			bool Entity::owner() const
			{
				return _owner;
			}

			void Entity::owner(bool value)
			{
				_owner = value;
			}

			bool Entity::enabled() const
			{
				return _enabled;
			}

			void Entity::enabled(bool value)
			{
				_enabled = value;
			}

			void Entity::componentsData(const std::string& value)
			{
				_componentsData = value;
			}

			const std::string& Entity::componentsData() const
			{
				return _componentsData;
			}

			void Entity::serialize(system::BinaryWriter& writer) const
			{
				writer << _id << _name << _originalName
					   << _owner << _enabled << _componentsData;
			}

			void Entity::unserialize(system::BinaryReader& reader)
			{
				reader >> _id >> _name >> _originalName
					   >> _owner >> _enabled >> _componentsData;
			}
		} // namespace types
	} // namespace network
} // namespace rtype
