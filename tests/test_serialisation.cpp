#include "catch.hpp"
#include "core/serialised_class.h" 
#include <vector>
#include <stdint.h>
#include <string>

class TestSerialiser
{
public:
	template<typename T> void SerialiseInteger(const char* name, T& data)
	{
		m_serialisedIntegers.push_back(IntResultPair(name, static_cast<int64_t>(data)));
	}
	template<typename T> void SerialiseReal(const char* name, T& data)
	{
		m_serialisedReals.push_back(RealResultPair(name, static_cast<double>(data)));
	}
	template<typename T> void SerialiseString(const char* name, T& data)
	{
		m_serialisedStrings.push_back(StringResultPair(name, data));
	}
	template<typename T> void SerialiseVector(const char* name, std::vector<T>& data)
	{
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			Core::Serialiser<TestSerialiser> serialiser(*this);
			serialiser.Serialise(name, *it);
		}
	}
	void SerialiseClassBegin(const char* name)
	{

	}
	void SerialiseClassEnd(const char* name)
	{

	}

	typedef std::pair<std::string, int64_t> IntResultPair;
	std::vector<IntResultPair> m_serialisedIntegers;

	typedef std::pair<std::string, double> RealResultPair;
	std::vector<RealResultPair> m_serialisedReals;

	typedef std::pair<std::string, std::string> StringResultPair;
	std::vector<StringResultPair> m_serialisedStrings;
};

class SerialisableClass
{
public:
	VOX_SERIALISABLE_CLASS(SerialisableClass)
	{
		VOX_SERIALISABLE_MEMBER(m_member0);
		VOX_SERIALISABLE_MEMBER(m_member1);
	}

	int m_member0;
	int m_member1;
};

class SerialisableClassInherited : public SerialisableClass
{
public:
	VOX_SERIALISABLE_CLASS(SerialisableClassInherited)
	{
		VOX_SERIALISE_BASE_CLASS(SerialisableClass);
		VOX_SERIALISABLE_MEMBER(m_member2);
	}
	int m_member2;
};

class SerialisableCompoundClass
{
public:
	VOX_SERIALISABLE_CLASS(SerialisableCompoundClass)
	{
		VOX_SERIALISABLE_MEMBER(m_c0);
		VOX_SERIALISABLE_MEMBER(m_c1);
	}

	SerialisableClass m_c0;
	SerialisableClassInherited m_c1;
};

TEST_CASE("Serialise POD types", "[Core::Serialisation]")
{
	TestSerialiser resultCatcher;
	Core::Serialiser<TestSerialiser> serialiser(resultCatcher);

	SECTION("Serialise integers")
	{
		int64_t test0 = 32;
		uint32_t test1 = 20;
		uint64_t test2 = 5000;

		VOX_SERIALISE(serialiser, test0);
		VOX_SERIALISE(serialiser, test1);
		VOX_SERIALISE(serialiser, test2);

		REQUIRE(resultCatcher.m_serialisedIntegers[0] == TestSerialiser::IntResultPair("test0", 32));
		REQUIRE(resultCatcher.m_serialisedIntegers[1] == TestSerialiser::IntResultPair("test1", 20));
		REQUIRE(resultCatcher.m_serialisedIntegers[2] == TestSerialiser::IntResultPair("test2", 5000));
	}

	SECTION("Serialise floats/doubles")
	{
		float test0 = 1.0f;
		double test1 = 8.0;

		VOX_SERIALISE(serialiser, test0);
		VOX_SERIALISE(serialiser, test1);

		REQUIRE(resultCatcher.m_serialisedReals[0] == TestSerialiser::RealResultPair("test0", 1.0f));
		REQUIRE(resultCatcher.m_serialisedReals[1] == TestSerialiser::RealResultPair("test1", 8.0));
	}

	SECTION("Serialise strings")
	{
		std::string testStr = "Testicles";
		VOX_SERIALISE(serialiser, testStr);
		REQUIRE(resultCatcher.m_serialisedStrings[0] == TestSerialiser::StringResultPair("testStr", "Testicles"));
	}

	SECTION("Serialise Vector")
	{
		std::vector<int> intVector = { 0, 3, 5, 7 };
		VOX_SERIALISE(serialiser, intVector);
		REQUIRE(resultCatcher.m_serialisedIntegers[0].second == 0);
		REQUIRE(resultCatcher.m_serialisedIntegers[1].second == 3);
		REQUIRE(resultCatcher.m_serialisedIntegers[2].second == 5);
		REQUIRE(resultCatcher.m_serialisedIntegers[3].second == 7);
	}

	SECTION("Serialise Vector of vectors")
	{
		std::vector<std::vector<std::string>> testVector;
		testVector.push_back({ "str0", "str1" });
		testVector.push_back({ "str2", "str3" });
		VOX_SERIALISE(serialiser, testVector);
		REQUIRE(resultCatcher.m_serialisedStrings[0].second == "str0");
		REQUIRE(resultCatcher.m_serialisedStrings[1].second == "str1");
		REQUIRE(resultCatcher.m_serialisedStrings[2].second == "str2");
		REQUIRE(resultCatcher.m_serialisedStrings[3].second == "str3");
	}

	SECTION("Serialise Class")
	{
		SerialisableClass testObject;
		testObject.m_member0 = 10;
		testObject.m_member1 = 30;
		VOX_SERIALISE(serialiser, testObject);
		REQUIRE(resultCatcher.m_serialisedIntegers[0] == TestSerialiser::IntResultPair("m_member0", 10));
		REQUIRE(resultCatcher.m_serialisedIntegers[1] == TestSerialiser::IntResultPair("m_member1", 30));

		SerialisableClassInherited testObjectInherited;
		testObjectInherited.m_member0 = 50;
		testObjectInherited.m_member1 = 70;
		testObjectInherited.m_member2 = 90;
		VOX_SERIALISE(serialiser, testObjectInherited);
		REQUIRE(resultCatcher.m_serialisedIntegers[2] == TestSerialiser::IntResultPair("m_member0", 50));
		REQUIRE(resultCatcher.m_serialisedIntegers[3] == TestSerialiser::IntResultPair("m_member1", 70));
		REQUIRE(resultCatcher.m_serialisedIntegers[4] == TestSerialiser::IntResultPair("m_member2", 90));
	}

	SECTION("Serialise Compound Class")
	{
		SerialisableCompoundClass testObject;
		testObject.m_c0.m_member0 = 10;
		testObject.m_c0.m_member1 = 30;
		testObject.m_c1.m_member0 = 50;
		testObject.m_c1.m_member1 = 70;
		testObject.m_c1.m_member2 = 90;
		VOX_SERIALISE(serialiser, testObject);
		REQUIRE(resultCatcher.m_serialisedIntegers[0] == TestSerialiser::IntResultPair("m_member0", 10));
		REQUIRE(resultCatcher.m_serialisedIntegers[1] == TestSerialiser::IntResultPair("m_member1", 30));
		REQUIRE(resultCatcher.m_serialisedIntegers[2] == TestSerialiser::IntResultPair("m_member0", 50));
		REQUIRE(resultCatcher.m_serialisedIntegers[3] == TestSerialiser::IntResultPair("m_member1", 70));
		REQUIRE(resultCatcher.m_serialisedIntegers[4] == TestSerialiser::IntResultPair("m_member2", 90));
	}
}