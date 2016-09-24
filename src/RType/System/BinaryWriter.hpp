#ifndef RTYPE_SYSTEM_BINARYWRITER_HPP_
#define RTYPE_SYSTEM_BINARYWRITER_HPP_

#include <cstdint>
#include <ostream>

namespace rtype
{
	namespace system
	{
		class BinaryWriter
		{
		public:
			enum EndianType
			{
				BIG,
				LITTLE
			};

		private:
			std::ostream& _stream;
			EndianType _type;
			uint8_t _buffer[8];

		public:
			BinaryWriter(std::ostream& stream, EndianType type = LITTLE);
			~BinaryWriter();

			BinaryWriter& operator<<(const uint8_t& value);
			BinaryWriter& operator<<(const uint16_t& value);
			BinaryWriter& operator<<(const uint32_t& value);

			BinaryWriter& operator<<(const int8_t& value);
			BinaryWriter& operator<<(const int16_t& value);
			BinaryWriter& operator<<(const int32_t& value);

			BinaryWriter& operator<<(const bool& value);
			BinaryWriter& operator<<(const std::string& value);

		private:
			void writeBuffer(size_t size);
		};
	} // namespace system
} // namespace rtype

#endif // RTYPE_SYSTEM_BINARTREADER_HPP_
