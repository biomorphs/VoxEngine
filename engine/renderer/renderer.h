/*
SDLEngine
Matt Hoyle
*/
#pragma once

#include "render_object_handle.h"

namespace Renderer
{
	class Device;
	class DeviceParameters;

	typedef RenderObjectHandle<Device> DeviceHandle;

	DeviceHandle CreateDevice(const DeviceParameters& dp);
}