#include <stdexcept>
#include <string>

#include "RType/System/BinaryWriter.hpp"
#include "RType/System/EndOfStreamError.hpp"

namespace rtype
{
	namespace system
	{
		BinaryWriter::BinaryWriter(std::ostream& stream, EndianType type)
			: _stream(stream), _type(type)
		{
		}

		BinaryWriter::~BinaryWriter()
		{
		}

		BinaryWriter& BinaryWriter::operator<<(const uint8_t& value)
		{
			_buffer[0] = static_cast<uint8_t>(value & 0xFF);
			writeBuffer(1);
			return *this;
		}

		BinaryWriter& BinaryWriter::operator<<(const uint16_t& value)
		{
			_buffer[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
			_buffer[1] = static_cast<uint8_t>(value & 0xFF);
			writeBuffer(2);
			return *this;
		}

		BinaryWriter& BinaryWriter::operator<<(const uint32_t& value)
		{
			_buffer[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
			_buffer[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
			_buffer[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
			_buffer[3] = static_cast<uint8_t>(value & 0xFF);
			writeBuffer(4);
			return *this;
		}

		BinaryWriter& BinaryWriter::operator<<(const int8_t& value)
		{
			return *this << static_cast<uint8_t>(value);
		}

		BinaryWriter& BinaryWriter::operator<<(const int16_t& value)
		{
			return *this << static_cast<uint16_t>(value);
		}

		BinaryWriter& BinaryWriter::operator<<(const int32_t& value)
		{
			return *this << static_cast<uint32_t>(value);
		}

		BinaryWriter& BinaryWriter::operator<<(const bool& value)
		{
			return *this << static_cast<uint8_t>(value ? 1 : 0);
		}

		BinaryWriter& BinaryWriter::operator<<(const std::string& value)
		{
			uint16_t size = static_cast<uint16_t>(value.size());
			if (size != value.size())
			{
				throw std::logic_error("String is invalid for BinaryWriter (got size "
					+ std::to_string(value.size()) + ")");
			}
			*this << size;
			if (!_stream.write(value.c_str(), value.size()))
				throw EndOfStreamError();
			return *this;
		}

		void BinaryWriter::writeBuffer(size_t size)
		{
			if (_type == BinaryWriter::LITTLE)
			{
				for (size_t i = 0; i < size / 2; ++i)
					std::swap(_buffer[i], _buffer[size - i - 1]);
			}
			if (!_stream.write(reinterpret_cast<char*>(_buffer), size))
				throw EndOfStreamError();
		}
	} // namespace system
} // namespace rtype
