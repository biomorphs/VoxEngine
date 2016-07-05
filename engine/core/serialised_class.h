/*
SDLEngine
Matt Hoyle
*/
#pragma once

#include <type_traits>
#include "traits.h"

namespace Core
{
	namespace Internal
	{
		template<typename T, typename InternalSerialiser, typename E = void>
		struct SerialiserImpl; // undefined serialiser for unknown types

		template<typename T, typename InternalSerialiser>	// serialise any sized integers
		struct SerialiserImpl<T, InternalSerialiser, typename std::enable_if<std::is_integral<T>::value>::type>
		{
			SerialiserImpl(InternalSerialiser& s, const char* name, T& data)
			{
				s.m_serialiser.SerialiseInteger(name, data);
			}
		};

		template<typename T, typename InternalSerialiser>	// serialise floats/doubles
		struct SerialiserImpl<T, InternalSerialiser, typename std::enable_if<std::is_floating_point<T>::value>::type>
		{
			SerialiserImpl(InternalSerialiser& s, const char* name, T& data)
			{
				s.m_serialiser.SerialiseReal(name, data);
			}
		};

		template<typename InternalSerialiser>	// std::string
		struct SerialiserImpl<std::string, InternalSerialiser>
		{
			SerialiserImpl(InternalSerialiser& s, const char* name, std::string& data)
			{
				s.m_serialiser.SerialiseString(name, data);
			}
		};

		template<typename T, typename InternalSerialiser> // vectors
		struct SerialiserImpl<std::vector<T>, InternalSerialiser>
		{
			SerialiserImpl(InternalSerialiser& s, const char* name, std::vector<T>& data)
			{
				s.m_serialiser.SerialiseVector(name, data);
			}
		};

		// Detects c_voxClassCanBeSerialised member in a object
		template <typename T>
		struct CanSerialise
		{
			typedef char(&yes)[1];
			typedef char(&no)[2];

			template <typename C> static yes check(decltype(&C::c_voxClassCanBeSerialised));
			template <typename> static no check(...);

			static bool const value = sizeof(check<T>(0)) == sizeof(yes);
		};

		template<typename T, typename InternalSerialiser>	// serialisable objects
		struct SerialiserImpl<T, InternalSerialiser, typename std::enable_if<CanSerialise<T>::value>::type>
		{
			SerialiserImpl(InternalSerialiser& s, const char* name, T& data)
			{
				s.m_serialiser.SerialiseClassBegin(name);
				data.Serialise(s);
				s.m_serialiser.SerialiseClassEnd(name);
			}
		};
	}

	class NullSerialiser	// All serialisers should implement this interface
	{
	public:
		template<typename T> void SerialiseInteger(const char* name, T& data) {}
		template<typename T> void SerialiseReal(const char* name, T& data) {}
		template<typename T> void SerialiseString(const char* name, T& data) {}
		template<typename T> void SerialiseVector(const char* name, std::vector<T>& data) {}
		void SerialiseClassBegin(const char* name) {}
		void SerialiseClassEnd(const char* name) {}
	};

	// Core serialiser proxy, uses SerialiserImpl to route calls to proper functions in 
	// InternalSerialiser using SFINAE and overloading
	template<typename InternalSerialiser>
	class Serialiser
	{
	public:
		Serialiser(InternalSerialiser& s) : m_serialiser(s) {}

		template <typename T>
		void Serialise(const char* name, T& data)
		{
			Internal::SerialiserImpl<T, Serialiser<InternalSerialiser>> serialise(*this, name, data);
		}

		InternalSerialiser& m_serialiser;
	};
};

// Serialise a single datum
#define VOX_SERIALISE(serialiser, data)	\
	serialiser.Serialise(#data, data);

// Add this to class definition if serialisation is required
#define VOX_SERIALISABLE_CLASS(className)	\
	static const bool c_voxClassCanBeSerialised = true;	\
	template<typename Serialiser> void Serialise(Serialiser& s)

#define VOX_SERIALISE_BASE_CLASS(baseClassName)	\
	baseClassName::Serialise(s)

// Use this for each member you want to serialise
#define VOX_SERIALISABLE_MEMBER(member)	\
	s.Serialise(#member, member);