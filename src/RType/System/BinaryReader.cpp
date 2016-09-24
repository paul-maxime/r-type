#include <vector>

#include "RType/System/BinaryReader.hpp"
#include "RType/System/EndOfStreamError.hpp"

namespace rtype
{
	namespace system
	{
		BinaryReader::BinaryReader(std::istream& stream, EndianType type)
			: _stream(stream), _type(type)
		{
		}

		BinaryReader::~BinaryReader()
		{
		}

		BinaryReader& BinaryReader::operator>>(uint8_t& value)
		{
			fillBuffer(1);
			value = _buffer[0];
			return *this;
		}

		BinaryReader& BinaryReader::operator>>(uint16_t& value)
		{
			fillBuffer(2);
			value =
				(static_cast<uint16_t>(_buffer[0]) << 8) |
				(static_cast<uint16_t>(_buffer[1]));
			return *this;
		}

		BinaryReader& BinaryReader::operator>>(uint32_t& value)
		{
			fillBuffer(4);
			value =
				(static_cast<uint32_t>(_buffer[0]) << 24) |
				(static_cast<uint32_t>(_buffer[1]) << 16) |
				(static_cast<uint32_t>(_buffer[2]) << 8) |
				(static_cast<uint32_t>(_buffer[3]));
			return *this;
		}

		BinaryReader& BinaryReader::operator>>(int8_t& value)
		{
			uint8_t uvalue;
			*this >> uvalue;
			value = static_cast<int8_t>(uvalue);
			return *this;
		}

		BinaryReader& BinaryReader::operator>>(int16_t& value)
		{
			uint16_t uvalue;
			*this >> uvalue;
			value = static_cast<int16_t>(uvalue);
			return *this;
		}

		BinaryReader& BinaryReader::operator>>(int32_t& value)
		{
			uint32_t uvalue;
			*this >> uvalue;
			value = static_cast<int32_t>(uvalue);
			return *this;
		}

		BinaryReader& BinaryReader::operator>>(bool& value)
		{
			uint8_t uvalue;
			*this >> uvalue;
			value = (uvalue != 0);
			return *this;
		}

		BinaryReader& BinaryReader::operator>>(std::string& value)
		{
			uint16_t size;
			*this >> size;
			if (size == 0)
			{
				value = "";
				return *this;
			}
			std::vector<char> buffer;
			buffer.resize(size);
			if (!_stream.read(&buffer[0], size))
				throw EndOfStreamError();
			value = std::string(buffer.begin(), buffer.end());
			return *this;
		}

		void BinaryReader::fillBuffer(size_t size)
		{
			if (!_stream.read(reinterpret_cast<char*>(_buffer), size))
				throw EndOfStreamError();
			if (_type == BinaryReader::LITTLE)
			{
				for (size_t i = 0; i < size / 2; ++i)
					std::swap(_buffer[i], _buffer[size - i - 1]);
			}
		}
	} // namespace system
} // namespace rtype
