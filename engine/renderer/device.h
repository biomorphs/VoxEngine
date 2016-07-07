/*
SDLEngine
Matt Hoyle
*/
#pragma once

#include "core\ref_counted.h"

namespace Renderer
{
	class DeviceParameters
	{
	public:
	};

	class Device : public Core::ReferenceCountedAtomic
	{
	public:
		Device();
		~Device();
		Device(Device&& other);
		Device& operator=(Device&& other);
		Device(const Device& other) = delete;
		Device& operator=(const Device& other) = delete;

		bool Create(const DeviceParameters& parameters);
		bool IsValid() const;
	private:
	};
}