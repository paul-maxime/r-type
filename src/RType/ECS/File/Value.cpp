#include <stdexcept>

#include "RType/ECS/File/Value.hpp"

namespace rtype
{
	namespace ecs
	{
		namespace file
		{
			const std::string Value::ENCODING = "UTF-8";

			Value::Value(const Json::Value& value)
				: _value(value)
			{
			}

			bool Value::hasField(const std::string& field) const
			{
				return _value.isMember(field);
			}

			std::vector<std::string> Value::fieldNames() const
			{
				return _value.getMemberNames();
			}

			size_t Value::size() const
			{
				return _value.size();
			}

			bool Value::isString() const
			{
				return _value.isString();
			}

			bool Value::isObject() const
			{
				return _value.isObject();
			}

			bool Value::isNumeric() const
			{
				return _value.isNumeric();
			}

			bool Value::isArray() const
			{
				return _value.isArray();
			}

			std::string Value::asString() const
			{
				return _value.asString();
			}

			bool Value::asBool() const
			{
				return _value.asBool();
			}

			int Value::asInt() const
			{
				return _value.asInt();
			}

			float Value::asFloat() const
			{
				return _value.asFloat();
			}

			std::string Value::getString(const std::string& field,
				const std::string& defaultValue) const
			{
				if (_value.isMember(field))
					return _value.get(field, ENCODING).asString();
				return defaultValue;
			}

			int Value::getInt(const std::string& field,
				int defaultValue) const
			{
				if (_value.isMember(field))
					return _value.get(field, ENCODING).asInt();
				return defaultValue;
			}

			bool Value::getBool(const std::string& field,
				bool defaultValue) const
			{
				if (_value.isMember(field))
					return _value.get(field, ENCODING).asBool();
				return defaultValue;
			}

			float Value::getFloat(const std::string& field,
				float defaultValue) const
			{
				if (_value.isMember(field))
					return _value.get(field, ENCODING).asFloat();
				return defaultValue;
			}

			Value Value::operator[](const std::string& field) const
			{
				if (!hasField(field))
					throw std::runtime_error("Tried to get the non-existing field `" +
						field + "'");
				return Value(_value[field]);
			}

			Value Value::operator[](size_t index) const
			{
				if (index >= size())
					throw std::runtime_error("Tried to get the non-existing index `" +
						std::to_string(index) + "'");
				return Value(_value[static_cast<int>(index)]);
			}
		} // namespace file
	} // namespace ecs
} // namespace rtype
