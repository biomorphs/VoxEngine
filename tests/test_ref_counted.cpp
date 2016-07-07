#include "catch.hpp"
#include "core/ref_counted.h"

class TestClass {};

TEST_CASE("Non-atomic ref counting correct", "[Core::RefCounted]")
{
	SECTION("Basic refcount correct")
	{
		Core::ReferenceCounted32 refCount32;
		REQUIRE(refCount32.GetReferenceCount() == 0);
		REQUIRE(refCount32.AddReference() == 1);
		REQUIRE(refCount32.AddReference() == 2);
		REQUIRE(refCount32.GetReferenceCount() == 2);
		REQUIRE(refCount32.RemoveReference() == 1);
		REQUIRE(refCount32.RemoveReference() == 0);
		REQUIRE(refCount32.GetReferenceCount() == 0);
	}

	SECTION("Move ctor")
	{
		Core::ReferenceCounted32 refCount0;
		refCount0.AddReference();
		refCount0.AddReference();
		refCount0.AddReference();
		REQUIRE(refCount0.GetReferenceCount() == 3);

		Core::ReferenceCounted32 refCount1 = std::move(refCount0);
		REQUIRE(refCount1.GetReferenceCount() == 3);
		REQUIRE(refCount0.GetReferenceCount() == 0);
		refCount1.RemoveReference();
		refCount1.RemoveReference();
		refCount1.RemoveReference();
		REQUIRE(refCount1.GetReferenceCount() == 0);
		REQUIRE(refCount0.GetReferenceCount() == 0);
	}
}

TEST_CASE("Atomic ref counting correct", "[Core::RefCounted]")
{
	SECTION("Basic refcount correct")
	{
		Core::ReferenceCountedAtomic refCount32;
		REQUIRE(refCount32.GetReferenceCount() == 0);
		REQUIRE(refCount32.AddReference() == 1);
		REQUIRE(refCount32.AddReference() == 2);
		REQUIRE(refCount32.GetReferenceCount() == 2);
		REQUIRE(refCount32.RemoveReference() == 1);
		REQUIRE(refCount32.RemoveReference() == 0);
		REQUIRE(refCount32.GetReferenceCount() == 0);
	}

	SECTION("Move ctor")
	{
		Core::ReferenceCountedAtomic refCount0;
		refCount0.AddReference();
		refCount0.AddReference();
		refCount0.AddReference();
		REQUIRE(refCount0.GetReferenceCount() == 3);

		Core::ReferenceCountedAtomic refCount1 = std::move(refCount0);
		REQUIRE(refCount1.GetReferenceCount() == 3);
		REQUIRE(refCount0.GetReferenceCount() == 0);
		refCount1.RemoveReference();
		refCount1.RemoveReference();
		refCount1.RemoveReference();
		REQUIRE(refCount1.GetReferenceCount() == 0);
		REQUIRE(refCount0.GetReferenceCount() == 0);
	}
}