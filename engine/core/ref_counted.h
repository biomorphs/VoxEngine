/*
SDLEngine
Matt Hoyle
*/
#pragma once

#include "platform\atomics.h"
#include <type_traits>

namespace Core
{
	template<typename RefcountImpl>
	class ReferenceCounted
	{
	public:
		ReferenceCounted();

		ReferenceCounted(ReferenceCounted<RefcountImpl>&& other);
		ReferenceCounted<RefcountImpl>& operator=(ReferenceCounted<RefcountImpl>&& other);

		ReferenceCounted(const ReferenceCounted<RefcountImpl>& other) = delete;
		ReferenceCounted<RefcountImpl>& operator=(const ReferenceCounted<RefcountImpl>& other) = delete;

		typename RefcountImpl::ReferenceType AddReference();
		typename RefcountImpl::ReferenceType RemoveReference();
		const typename RefcountImpl::ReferenceType GetReferenceCount() const;

	private:
		RefcountImpl m_refCountImpl;
	};

	template<typename InternalType>
	class NonAtomicRefCount
	{
	public:
		NonAtomicRefCount();
		NonAtomicRefCount(NonAtomicRefCount<InternalType>&& other);
		NonAtomicRefCount(const NonAtomicRefCount<InternalType>& other) = delete;
		NonAtomicRefCount& operator=(const NonAtomicRefCount<InternalType>& other) = delete;
		NonAtomicRefCount& operator=(NonAtomicRefCount<InternalType>&& other);
		InternalType AddRef();
		InternalType RemoveRef();
		InternalType GetRefCount() const;
		typedef InternalType ReferenceType;
	private:
		InternalType m_refCount;
	};

	class AtomicRefCount
	{
	public:
		AtomicRefCount();
		AtomicRefCount(AtomicRefCount&& other);
		AtomicRefCount(const AtomicRefCount& other) = delete;
		AtomicRefCount& operator=(const AtomicRefCount& other) = delete;
		AtomicRefCount& operator=(AtomicRefCount&& other);
		int32_t AddRef();
		int32_t RemoveRef();
		int32_t GetRefCount() const;
		typedef int32_t ReferenceType;
	private:
		Platform::AtomicInt32 m_refCount;
	};

	typedef ReferenceCounted<NonAtomicRefCount<int32_t>> ReferenceCounted32;
	typedef ReferenceCounted<NonAtomicRefCount<int64_t>> ReferenceCounted64;
	typedef ReferenceCounted<AtomicRefCount> ReferenceCountedAtomic;
}

#include "ref_counted_impl.inl"