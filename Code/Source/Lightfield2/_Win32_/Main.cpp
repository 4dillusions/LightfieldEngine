/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "..\..\Engine\GameEngine\LFGameEngine.h"

using namespace LFEngine::GameEngine;

#ifdef _WINDOWS
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
#else
void main()
#endif
{
	LFGameEngine::CreateInstance();
	LFGameEngine::ReleaseInstance();

	LFCore::Common::LFMemoryManager::Instance().CheckMemoryLeaks();

#ifdef _WINDOWS
	return 0;
#else
	system("pause");
#endif
}

#endif
