/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "..\Main.h"
#include "..\..\LFEngine\LFCore\LFCommon\LFSystemData.h"
#include "..\..\LFEngine\LFData\LFAppData.h"

int main(int argc, char *argv[])
{
	LFSystemData::SetAppData({ argc, false, argv, "unittest", "com.dillusions.unittest" });
	LF3Engine::LFUnitTest::LFUnitTestMain::Run();

	system("pause");
	return 0;
}

#endif
