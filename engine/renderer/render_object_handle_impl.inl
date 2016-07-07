/*
SDLEngine
Matt Hoyle
*/
#pragma once
namespace Renderer
{
	template <typename RenderObject>
	RenderObjectHandle<RenderObject>::RenderObjectHandle()
		: m_object(nullptr)
		, m_deleter(nullptr)
	{
	}

	template <typename RenderObject>
	RenderObjectHandle<RenderObject>::RenderObjectHandle(RenderObject* object, const Deleter& deleter)
		: m_object(object)
		, m_deleter(deleter)
	{
		m_object->AddReference();
	}

	template <typename RenderObject>
	RenderObjectHandle<RenderObject>::~RenderObjectHandle()
	{
		if (m_object != nullptr)
		{
			if (m_object->RemoveReference() == 0)
			{
				m_deleter(m_object);
			}
		}
	}

	template <typename RenderObject>
	bool RenderObjectHandle<RenderObject>::IsValid() const
	{
		return m_object != nullptr && m_object->IsValid();
	}

	template <typename RenderObject>
	RenderObjectHandle<RenderObject>::RenderObjectHandle(const RenderObjectHandle& other)
	{
		if (other.m_object != nullptr)
		{
			other.m_object->AddReference();
		}
		m_object = other.m_object;
		m_deleter = other.m_deleter;
	}

	template <typename RenderObject>
	RenderObjectHandle<RenderObject>& RenderObjectHandle<RenderObject>::operator=(const RenderObjectHandle& other)
	{
		if (other.m_object != nullptr)
		{
			other.m_object->AddReference();
		}
		if (m_object != nullptr)
		{
			m_object->RemoveReference();
		}
		m_object = other.m_object;
		m_deleter = other.m_deleter;
		return *this;
	}
}