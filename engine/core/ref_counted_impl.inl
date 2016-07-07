/*
SDLEngine
Matt Hoyle
*/
#pragma once

namespace Core
{

	template<typename RefcountImpl>
	inline ReferenceCounted<RefcountImpl>::ReferenceCounted()
	{
	}

	template<typename RefcountImpl>
	inline ReferenceCounted<RefcountImpl>::ReferenceCounted(ReferenceCounted<RefcountImpl>&& other)
		: m_refCountImpl(std::move(other.m_refCountImpl))
	{
	}

	template<typename RefcountImpl>
	inline ReferenceCounted<RefcountImpl>& ReferenceCounted<RefcountImpl>::operator=(ReferenceCounted<RefcountImpl>&& other)
	{
		m_refCountImpl = std::move(other.m_refCountImpl);
	}

	template<typename RefcountImpl>
	inline typename RefcountImpl::ReferenceType ReferenceCounted<RefcountImpl>::AddReference()
	{
		return m_refCountImpl.AddRef();
	}

	template<typename RefcountImpl>
	inline typename RefcountImpl::ReferenceType ReferenceCounted<RefcountImpl>::RemoveReference()
	{
		return m_refCountImpl.RemoveRef();
	}

	template<typename RefcountImpl>
	inline const typename RefcountImpl::ReferenceType ReferenceCounted<RefcountImpl>::GetReferenceCount() const
	{
		return m_refCountImpl.GetRefCount();
	}

	template<typename InternalType>
	inline NonAtomicRefCount<InternalType>::NonAtomicRefCount()
		: m_refCount(0)
	{
	}

	template<typename InternalType>
	inline NonAtomicRefCount<InternalType>::NonAtomicRefCount(NonAtomicRefCount<InternalType>&& other)
		: m_refCount(other.m_refCount)
	{
		other.m_refCount = 0;
	}

	template<typename InternalType>
	inline NonAtomicRefCount<InternalType>& NonAtomicRefCount<InternalType>::operator=(NonAtomicRefCount<InternalType>&& other)
	{
		m_refCount = other.m_refCount;
		other.m_refCount = 0;
		return m_refCount;
	}

	template<typename InternalType>
	inline InternalType NonAtomicRefCount<InternalType>::AddRef()
	{
		return ++m_refCount;
	}

	template<typename InternalType>
	inline InternalType NonAtomicRefCount<InternalType>::RemoveRef()
	{
		return --m_refCount;
	}

	template<typename InternalType>
	inline InternalType NonAtomicRefCount<InternalType>::GetRefCount() const
	{
		return m_refCount;
	}

	inline AtomicRefCount::AtomicRefCount()
		: m_refCount(0)
	{
	}

	inline AtomicRefCount::AtomicRefCount(AtomicRefCount&& other)
		: m_refCount(other.m_refCount.Get())
	{
		other.m_refCount.Set(0);
	}

	inline AtomicRefCount& AtomicRefCount::operator=(AtomicRefCount&& other)
	{
		m_refCount = other.m_refCount;
		other.m_refCount.Set(0);
		return *this;
	}

	inline int32_t AtomicRefCount::AddRef()
	{
		return m_refCount.Add(1) + 1;
	}

	inline int32_t AtomicRefCount::RemoveRef()
	{
		return m_refCount.Add(-1) - 1;
	}

	inline int32_t AtomicRefCount::GetRefCount() const
	{
		return m_refCount.Get();
	}
}