#include "SMSystemInfo.h"
#include "FSysSystemInfo.h"
#include "FSysRuntimeInfo.h"
#include <FSystem.h>

using namespace Osp::System;

namespace SMEngine { namespace Engine
{
	SMSystemInfo SMSystemInfo::instance;

	SMSystemInfo::SMSystemInfo()
	{ }

	int SMSystemInfo::ScreenWidth()
	{
		int result;
		SystemInfo::GetValue("ScreenWidth", result);

		return result;
	}

	int SMSystemInfo::ScreenHeight()
	{
		int result;
		SystemInfo::GetValue("ScreenHeight", result);

		return result;
	}

	float SMSystemInfo::AvailableMemory()
	{
		float result;
		int temp;
		RuntimeInfo::GetValue("AvailableMemory", temp);
		result = temp / 1024.0f;
		result /= 1024.0f;

		return result;
	}

	float SMSystemInfo::AllocatedMemory()
	{
		float result;
		int temp;
		RuntimeInfo::GetValue("AllocatedMemory", temp);
		result = temp / 1024.0f;
		result /= 1024.0f;

		return result;
	}

	float SMSystemInfo::MaxAllocatableMemory()
	{
		float result;
		int temp;
		RuntimeInfo::GetValue("MaxAllocatableMemory", temp);
		result = temp / 1024.0f;
		result /= 1024.0f;

		return result;
	}

	float SMSystemInfo::AvailableVideoMemory()
	{
		float result;
		int temp;
		RuntimeInfo::GetValue("AvailableVideoMemory", temp);
		result = temp / 1024.0f;
		result /= 1024.0f;

		return result;
	}

	SMString SMSystemInfo::DateTime()
	{
		SMString result;

		result.Append(__DATE__);
		result.Append(" ");
		result.Append(__TIME__);

		return result;
	}

	bool SMSystemInfo::IsSilentMode()
	{
		bool result;

		SettingInfo::GetValue("SilentMode", result);

		return result;
	}
};};
