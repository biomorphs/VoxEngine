#include "catch.hpp"
#include "renderer\renderer.h"
#include "renderer\device.h"

TEST_CASE("Renderer creates device", "[Renderer]")
{
	Renderer::DeviceParameters dp;

	Renderer::DeviceHandle device = Renderer::CreateDevice(dp);
	REQUIRE(device.IsValid());
}