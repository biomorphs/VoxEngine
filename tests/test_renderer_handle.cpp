#include "catch.hpp"
#include "core\ref_counted.h"
#include "renderer\render_object_handle.h"

struct SimpleTestObject : public Core::ReferenceCounted32
{
};

TEST_CASE("Render handle is good", "[Renderer::RenderObjectHandle]")
{
	int32_t deleterCalled = 0;
	auto deleter = [&deleterCalled](SimpleTestObject* obj)
	{
		deleterCalled++;
	};
	SimpleTestObject* newObject = new SimpleTestObject;
	REQUIRE(newObject->GetReferenceCount() == 0);

	SECTION("Deleter called on 0 ref")
	{
		{
			Renderer::RenderObjectHandle<SimpleTestObject> testHandle(newObject, deleter);
			REQUIRE(newObject->GetReferenceCount() == 1);
		}
		REQUIRE(deleterCalled == 1);
		REQUIRE(newObject->GetReferenceCount() == 0);
	}

	SECTION("Copy ctor/operator is ok")
	{
		{
			Renderer::RenderObjectHandle<SimpleTestObject> testHandle(newObject, deleter);
			REQUIRE(newObject->GetReferenceCount() == 1);

			Renderer::RenderObjectHandle<SimpleTestObject> testHandleCopy1(testHandle);
			REQUIRE(newObject->GetReferenceCount() == 2);

			Renderer::RenderObjectHandle<SimpleTestObject> testHandleCopy2 = testHandleCopy1;
			REQUIRE(newObject->GetReferenceCount() == 3);

			testHandleCopy2 = testHandleCopy1;
			REQUIRE(newObject->GetReferenceCount() == 3);
		}
		REQUIRE(deleterCalled == 1);
		REQUIRE(newObject->GetReferenceCount() == 0);
	}

	delete newObject;
}