#ifndef RTYPE_NETWORK_TYPES_ENTITY_HPP_
#define RTYPE_NETWORK_TYPES_ENTITY_HPP_

#include <vector>

#include "RType/System/BinaryWriter.hpp"
#include "RType/System/BinaryReader.hpp"

namespace rtype
{
	namespace network
	{
		namespace types
		{
			class Entity
			{
			private:
				uint32_t _id;
				std::string _name;
				std::string _originalName;
				bool _owner;
				bool _enabled;
				std::string _componentsData;

			public:
				uint32_t id() const;
				void id(uint32_t);

				const std::string& name() const;
				void name(const std::string&);

				const std::string& originalName() const;
				void originalName(const std::string&);

				bool owner() const;
				void owner(bool);

				bool enabled() const;
				void enabled(bool);

				const std::string& componentsData() const;
				void componentsData(const std::string&);

				void serialize(system::BinaryWriter&) const;
				void unserialize(system::BinaryReader&);
			};
		} // namespace types
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_TYPES_ENTITY_HPP_
