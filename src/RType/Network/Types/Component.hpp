#ifndef RTYPE_NETWORK_TYPES_COMPONENT_HPP_
#define RTYPE_NETWORK_TYPES_COMPONENT_HPP_

#include <string>

#include "RType/System/BinaryWriter.hpp"
#include "RType/System/BinaryReader.hpp"

namespace rtype
{
	namespace network
	{
		namespace types
		{
			class Component
			{
			private:
				std::string _type;
				std::string _data;

			public:
				const std::string& type() const;
				void type(const std::string&);

				const std::string& data() const;
				void data(const std::string&);

				void serialize(system::BinaryWriter&) const;
				void unserialize(system::BinaryReader&);
			};
		} // namespace types
	} // namespace network
} // namespace rtype

#endif // RTYPE_NETWORK_TYPES_COMPONENT_HPP_
