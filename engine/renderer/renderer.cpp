/*
SDLEngine
Matt Hoyle
*/
#include "renderer.h"
#include "device.h"

namespace Renderer
{
	void DestroyDevice(Device* d)
	{
		delete d;
	}

	DeviceHandle CreateDevice(const DeviceParameters& dp)
	{
		Device* newDevice = new Device();
		DeviceHandle newHandle;
		if (newDevice->Create(dp) == true)
		{
			newHandle = DeviceHandle(newDevice, DestroyDevice);
		}
		return newHandle;
	}
}