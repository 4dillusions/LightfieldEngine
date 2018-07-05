/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFMemoryManager.h"
#include "LFString.h"
#include "..\LFPatterns\LFIoc.h"
#include "..\LFIO\LFLogger.h"

using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFPatterns;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	std::unordered_map<int, const char *> LFMemoryManager::memoryList;

	int LFMemoryManager::GetMemoryLeakCount()
	{
		return memoryList.size();
	}

	void LFMemoryManager::Add(int address, const char *info)
	{
		memoryList.insert({ address, info });
	}

	void LFMemoryManager::Remove(int address)
	{
		auto search = memoryList.find(address);
		if (search != memoryList.end())
			memoryList.erase(search);
	}

	void LFMemoryManager::WriteStatistics(bool isTest)
	{
		LFIoc<LFLogger>::Get().ReleaseBuffer();

		LFIoc<LFLogger>::Get().WriteOutput("");
		LFIoc<LFLogger>::Get().WriteOutput("Leaked objects:");

		for (auto i : memoryList)
			LFIoc<LFLogger>::Get().WriteOutput(i.second);

		if (memoryList.size() == 0)
			LFIoc<LFLogger>::Get().WriteOutput("0 leaked object");

		if (!isTest)
		{
			LFIoc<LFLogger>::Get().WriteOutput("");
			LFIoc<LFLogger>::Get().WriteOutput("Warnings:");
			LFIoc<LFLogger>::Get().WriteOutput(LFIoc<LFLogger>::Get().GetWarnings());

			LFIoc<LFLogger>::Get().WriteOutput("");
			LFIoc<LFLogger>::Get().WriteOutput("Errors:");
			LFIoc<LFLogger>::Get().WriteOutput(LFIoc<LFLogger>::Get().GetErrors());
		}

		LFIoc<LFLogger>::Get().WriteOutput("");
	}
}}}}
