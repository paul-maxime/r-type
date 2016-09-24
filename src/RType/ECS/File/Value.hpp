#ifndef RTYPE_ECS_FILE_VALUE_HPP_
#define RTYPE_ECS_FILE_VALUE_HPP_

#include <string>
#include <vector>

#include "json/reader.h"

namespace rtype
{
	namespace ecs
	{
		namespace file
		{
			class Value
			{
			private:
				static const std::string ENCODING;

			public:
				explicit Value(const Json::Value& value);

				bool hasField(const std::string& field) const;
				std::vector<std::string> fieldNames() const;
				size_t size() const;

				bool isString() const;
				bool isObject() const;
				bool isNumeric() const;
				bool isArray() const;

				std::string asString() const;
				int asInt() const;
				float asFloat() const;
				bool asBool() const;

				std::string getString(const std::string& field,
					const std::string& defaultValue = "") const;

				int getInt(const std::string& field,
					int defaultValue = 0) const;

				bool getBool(const std::string& field,
					bool defaultValue = false) const;

				float getFloat(const std::string& field,
					float defaultValue = 0.0f) const;

				Value operator[](const std::string& field) const;
				Value operator[](size_t index) const;

			private:
				Json::Value _value;
			};
		} // namespace file
	} // namespace ecs
} // namespace rtype

#endif // !RTYPE_ECS_FILE_VALUE_HPP_
