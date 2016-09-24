#include <iostream>
#include <sstream>

#include "RType/System/BinaryReader.hpp"
#include "RType/System/BinaryWriter.hpp"

static const char* g_title;
static int g_errors;

void check(bool expression, const char* name)
{
	if (!expression)
	{
		std::cerr << "test `" << g_title << "-" << name << "' failed" << std::endl;
		++g_errors;
	}
}

void test_binary_writer_little()
{
	g_title = "BinaryWriter-LittleEndian";

	std::ostringstream oss;
	rtype::system::BinaryWriter writer(oss);

	writer << static_cast<uint8_t>(0x55)
		   << static_cast<uint16_t>(0xABCD)
		   << static_cast<uint32_t>(0x12345678)
		   << "STRING";

	std::string result(oss.str());

	check(result.size() == 15, "ResultSize");

	check(static_cast<uint8_t>(result[0]) == 0x55, "uint8");
	check(static_cast<uint8_t>(result[1]) == 0xCD &&
		static_cast<uint8_t>(result[2]) == 0xAB, "uint16");
	check(static_cast<uint8_t>(result[3]) == 0x78 &&
		static_cast<uint8_t>(result[4]) == 0x56 &&
		static_cast<uint8_t>(result[5]) == 0x34 &&
		static_cast<uint8_t>(result[6]) == 0x12, "uint32");

	check(result[7] == 0x06 &&
		  result[8] == 0x00, "StringSize");
	check(result[ 9] == 'S' &&
		  result[10] == 'T' &&
		  result[11] == 'R' &&
		  result[12] == 'I' &&
		  result[13] == 'N' &&
		  result[14] == 'G', "StringContent");
}

void test_binary_writer_big()
{
	g_title = "BinaryWriter-BigEndian";

	std::ostringstream oss;
	rtype::system::BinaryWriter writer(oss, rtype::system::BinaryWriter::BIG);

	writer << static_cast<uint8_t>(0x55)
		   << static_cast<uint16_t>(0xABCD)
		   << static_cast<uint32_t>(0x12345678)
		   << "STRING";

	std::string result(oss.str());

	check(result.size() == 15, "ResultSize");


	check(static_cast<uint8_t>(result[0]) == 0x55, "uint8");
	check(static_cast<uint8_t>(result[2]) == 0xCD &&
		static_cast<uint8_t>(result[1]) == 0xAB, "uint16");
	check(static_cast<uint8_t>(result[6]) == 0x78 &&
		static_cast<uint8_t>(result[5]) == 0x56 &&
		static_cast<uint8_t>(result[4]) == 0x34 &&
		static_cast<uint8_t>(result[3]) == 0x12, "uint32");

	check(result[8] == 0x06 &&
		  result[7] == 0x00, "StringSize");
	check(result[ 9] == 'S' &&
		  result[10] == 'T' &&
		  result[11] == 'R' &&
		  result[12] == 'I' &&
		  result[13] == 'N' &&
		  result[14] == 'G', "StringContent");
}

void test_binary_reader_little()
{
	g_title = "BinaryReader-LittleEndian";

	std::string content("\x55\xCD\xAB\x78\x56\x34\x12\x06\x00STRING", 15);

	std::istringstream iss(content);
	rtype::system::BinaryReader reader(iss);

	uint8_t v8;
	uint16_t v16;
	uint32_t v32;
	std::string vstr;

	reader >> v8 >> v16 >> v32 >> vstr;

	check(v8 == 0x55, "uint8");
	check(v16 == 0xABCD, "uint16");
	check(v32 == 0x12345678, "uint32");
	check(vstr.size() == 6, "StringSize");
	check(vstr == "STRING", "StringContent");
}

void test_binary_reader_big()
{
	g_title = "BinaryReader-BigEndian";

	std::string content("\x55\xAB\xCD\x12\x34\x56\x78\x00\x06STRING", 15);

	std::istringstream iss(content);
	rtype::system::BinaryReader reader(iss, rtype::system::BinaryReader::BIG);

	uint8_t v8;
	uint16_t v16;
	uint32_t v32;
	std::string vstr;

	reader >> v8 >> v16 >> v32 >> vstr;

	check(v8 == 0x55, "uint8");
	check(v16 == 0xABCD, "uint16");
	check(v32 == 0x12345678, "uint32");
	check(vstr.size() == 6, "StringSize");
	check(vstr == "STRING", "StringContent");
}

void test_binary_use()
{
	g_title = "BinaryUse-LittleEndian";

	std::ostringstream oss;
	rtype::system::BinaryWriter writer(oss);

	writer << static_cast<uint8_t>(0xF1)
		   << static_cast<uint16_t>(0xFEED)
		   << static_cast<uint32_t>(0xBECABECA)
		   << static_cast<int8_t>(-42)
		   << static_cast<int16_t>(-9999)
		   << static_cast<int32_t>(-1234567890)
		   << "This is a test!"
		   << ""
		   << "Another test";

	std::string content = oss.str();

	std::istringstream iss(content);
	rtype::system::BinaryReader reader(iss);

	uint8_t vu8;
	uint16_t vu16;
	uint32_t vu32;
	int8_t v8;
	int16_t v16;
	int32_t v32;
	std::string str1;
	std::string str2;
	std::string str3;

	reader >> vu8 >> vu16 >> vu32
		   >> v8 >> v16 >> v32
		   >> str1 >> str2 >> str3;

	check(vu8 == 0xF1, "uint8");
	check(vu16 == 0xFEED, "uint16");
	check(vu32 == 0xBECABECA, "uint32");
	check(v8 == -42, "int8");
	check(v16 == -9999, "int16");
	check(v32 == -1234567890, "int32");
	check(str1 == "This is a test!", "String1");
	check(str2 == "", "EmptyString");
	check(str3 == "Another test", "String2");
}

int main()
{
	test_binary_writer_little();
	test_binary_writer_big();
	test_binary_reader_little();
	test_binary_reader_big();
	test_binary_use();

	if (g_errors)
	{
		std::cout << g_errors << " error(s)." << std::endl;
		return EXIT_FAILURE;
	}
	else
	{
		std::cout << "no errors." << std::endl;
		return EXIT_SUCCESS;
	}
}
