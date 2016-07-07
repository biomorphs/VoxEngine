/*
SDLEngine
Matt Hoyle
*/
#include "device.h"

namespace Renderer
{
	Device::Device()
	{
	}

	Device::~Device()
	{
	}

	Device::Device(Device&& other)
	{
	}

	Device& Device::operator=(Device&& other)
	{
		return *this;
	}

	bool Device::IsValid() const
	{
		return true;
	}

	bool Device::Create(const DeviceParameters& parameters)
	{
		return true;
	}
}