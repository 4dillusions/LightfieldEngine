#pragma once

#include "..\\Core\\SMString.h"

using namespace SMEngine::Core;

namespace SMEngine { namespace Engine
{
	/*
	�ltal�nos rendszer inform�ci�k. Singleton.
	*/
	class SMSystemInfo
	{
	private:
		SMSystemInfo();

		static SMSystemInfo instance;

	public:
		static SMSystemInfo &Instance() { return instance; }

		int ScreenWidth();
		int ScreenHeight();
		float AvailableMemory();
		float AllocatedMemory();
		float MaxAllocatableMemory();
		float AvailableVideoMemory();
		SMString DateTime();

		bool IsSilentMode();
	};
};};
