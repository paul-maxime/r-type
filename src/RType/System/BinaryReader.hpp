#ifndef RTYPE_SYSTEM_BINARYREADER_HPP_
#define RTYPE_SYSTEM_BINARYREADER_HPP_

#include <cstdint>
#include <istream>

namespace rtype
{
	namespace system
	{
		class BinaryReader
		{
		public:
			enum EndianType
			{
				BIG,
				LITTLE
			};

		private:
			std::istream& _stream;
			EndianType _type;
			uint8_t _buffer[8];

		public:
			BinaryReader(std::istream& stream, EndianType type = LITTLE);
			virtual ~BinaryReader();

			virtual BinaryReader& operator>>(uint8_t& value);
			virtual BinaryReader& operator>>(uint16_t& value);
			virtual BinaryReader& operator>>(uint32_t& value);

			virtual BinaryReader& operator>>(int8_t& value);
			virtual BinaryReader& operator>>(int16_t& value);
			virtual BinaryReader& operator>>(int32_t& value);

			virtual BinaryReader& operator>>(bool& value);
			virtual BinaryReader& operator>>(std::string& value);

		private:
			void fillBuffer(size_t size);
		};
	} // namespace system
} // namespace rtype

#endif // RTYPE_SYSTEM_BINARTREADER_HPP_
