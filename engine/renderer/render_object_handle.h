/*
SDLEngine
Matt Hoyle
*/
#pragma once
#include <functional>

namespace Renderer
{
	template <typename RenderObject>
	class RenderObjectHandle
	{
	public:
		typedef std::function<void(RenderObject*)> Deleter;

		RenderObjectHandle();
		RenderObjectHandle(RenderObject* object, const Deleter& deleter);
		~RenderObjectHandle();
		RenderObjectHandle(const RenderObjectHandle& other);
		RenderObjectHandle& operator=(const RenderObjectHandle& other);

		bool IsValid() const;

	private:
		RenderObject* m_object;
		Deleter m_deleter;
	};
}

#include "render_object_handle_impl.inl"