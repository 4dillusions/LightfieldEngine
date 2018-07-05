/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "..\Collections\LFDictionary.h"
#include "..\IO\LFLogger.h"

#include "..\Common\LFString.h"

namespace LFCore { namespace Common
{
	LFMemoryManager LFMemoryManager::instance;
	LFCore::Collections::LFDictionary<int, const char *> memoryList(false);
	
	int LFMemoryManager::MemoryLeakCount()
	{
		return memoryList.Length();
	}

	void LFMemoryManager::Add(int address, const char *info)
	{
		memoryList.Add(address, info);
	}

	void LFMemoryManager::Remove(int address)
	{
		memoryList.Remove(address);
	}

	void LFMemoryManager::CheckMemoryLeaks()
	{
		#if defined(DEBUG)
		LFCore::IO::LFLogger::Instance().WriteOutput("");
		LFCore::IO::LFLogger::Instance().WriteOutput("LFMemoryManager - Leaked objects:");

		for (memoryList.First(); memoryList.IsDone(); memoryList.Next())
			LFCore::IO::LFLogger::Instance().WriteOutput(memoryList.Current());

		if (memoryList.Length() == 0)
			LFCore::IO::LFLogger::Instance().WriteOutput("0 leaked object");

		LFCore::IO::LFLogger::Instance().WriteOutput("");
		#endif
	}
}}
