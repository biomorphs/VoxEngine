/*
SDLEngine
Matt Hoyle
*/
#pragma once

namespace Core
{
	// Helper using SFINAE to detect a member with a specific name. Note the type is NOT tested
	template <typename T, typename MemberName>
	struct HasMemberNamed
	{
		typedef char(&yes)[1];
		typedef char(&no)[2];

		template <typename C> static yes check(decltype(&C::MemberName));
		template <typename> static no check(...);

		static bool const value = sizeof(check<T>(0)) == sizeof(yes);
	};
}