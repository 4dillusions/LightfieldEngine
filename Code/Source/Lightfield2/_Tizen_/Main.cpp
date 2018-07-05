/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#include "..\..\..\LFEngine\src\GameEngine\LFGameEngine.h"
#include "..\..\..\LFEngine\src\Render\_Tizen_\LFRenderWindowTizen.h"
#include "..\..\..\LFCore\src\IO\LFLogger.h"
#include <tizen.h>

using namespace LFEngine::GameEngine;

int main(int argc, char *argv[])
{
	MainDataHelper::mainData.argc = argc;
	MainDataHelper::mainData.argv = argv;

	LFCore::IO::LFLogger::Instance().LogTag((char *)LOG_TAG);

	LFGameEngine::CreateInstance();
	LFGameEngine::ReleaseInstance();

	LFCore::Common::LFMemoryManager::Instance().CheckMemoryLeaks();

	return MainDataHelper::mainData.returnValue;
}

#endif
