/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "IOTest.h"
#include "..\Test.h"
#include "..\..\Core\Common\LFVFSManager.h"
#include "..\..\Core\IO\LFSerializer.h"

#ifdef TIZEN
#include <app_common.h>
#endif

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace UnitTest
{
	struct TestData 
	{ 
		int volumeSFX;
		int volumeMusic;
		int x[5]; 
	};

	void IOTest::SerializerTest()
	{
		LFVFSManager::CreateInstance();

		LFString path;

		#ifdef WIN32
		path += "Home/Data/";
		#endif

		#ifdef TIZEN
		path += app_get_data_path();
		#endif

		LFVFSManager::Instance()->AddPath(LFVFSManager::CP_DATA_SAVE, path.ToNewChar());

		TestData data;
		for (int i = 0; i < 5; ++i)
			data.x[i] = 1;

		data.x[0] = 22;
		data.volumeSFX = 20;
		data.volumeMusic = 55;

		const char *fileName = "testData.dat";
		LFSerializer<TestData> ser;
		ser.WriteBinaryData(fileName, data, LFVFSManager::CP_DATA_SAVE);

		TestData data2 = ser.ReadBinaryData(fileName, LFVFSManager::CP_DATA_SAVE);
		int dataArrayNum = 0;
		for (int i = 0; i < 5; ++i)
			dataArrayNum += data2.x[i];

		Test::AssertOk(dataArrayNum == 26 && data2.volumeSFX == 20 && data2.volumeMusic == 55, "LFCore::IO::LFIOTest::SMSerializerTest");

		LFVFSManager::ReleaseInstance();
	}
};
