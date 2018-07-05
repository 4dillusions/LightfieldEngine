/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFIOTest.h"
#include "..\..\LFTest.h"
#include "..\..\..\LFEngine\LFCore\LFIO\LFSerializer.h"
#include "..\..\..\LFEngine\LFCore\LFIO\LFFile.h"
#include "..\..\..\LFEngine\LFCore\LFMath\LFRandom.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFString.h"
#include "..\..\..\LFEngine\LFCore\LFIO\LFJson.h"
#include "..\..\..\LFEngine\LFCore\LFCollections\LFList.h"
#include "../../../LFEngine/LFCore/LFIO/LFTextRW.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFMath;
using namespace LF3Engine::LFEngine::LFCore::LFCollections;

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFCore
{
	struct TestData final
	{
		int volumeSFX;
		int volumeMusic;
		int x[5];
	};

	void LFIOTest::LFSerializerStaticBinaryTest()
	{
		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();

		const char *fileName = "testStaticData.dat";
		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, fileName))
			LFFile::Delete(LFVFSPath::DataReadWrite, fileName);

		TestData data;
		for (int i = 0; i < 5; ++i)
			data.x[i] = 1;

		int dataX = LFRandom::CreateRandom(1, 20);
		int dataVolumeSFX = LFRandom::CreateRandom(1, 100);
		int dataVolumeMusic = LFRandom::CreateRandom(1, 100);
		data.x[0] = dataX;
		data.volumeSFX = dataVolumeSFX;
		data.volumeMusic = dataVolumeMusic;

		LFSerializer<TestData> ser;
		ser.WriteStaticBinaryData(LFVFSPath::DataReadWrite, fileName, data);

		bool isWriteDataExist = LFFile::IsFileExist(LFVFSPath::DataReadWrite, fileName);
        bool isContentExist = LFFile::IsFileExist(LFVFSPath::DataRead, "Placeholder.txt");

		TestData data2 = ser.ReadStaticBinaryData(LFVFSPath::DataReadWrite, fileName);
		int dataArrayNum = 0;
		for (int i = 0; i < 5; ++i)
			dataArrayNum += data2.x[i];

		LFTest::AssertOk(isWriteDataExist, INFO);
		LFTest::AssertOk(isContentExist, INFO);
		LFTest::AssertOk(dataArrayNum == dataX + 4 && data2.volumeSFX == dataVolumeSFX && data2.volumeMusic == dataVolumeMusic, INFO);

		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, fileName))
            LFFile::Delete(LFVFSPath::DataReadWrite, fileName);

		LFIoc<LFVFSManager *>::Release();
	}

	void LFIOTest::LFSerializerDynamicBinaryTest()
	{
		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();

		const char *fileName = "testDynamicData.dat";
		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, fileName))
			LFFile::Delete(LFVFSPath::DataReadWrite, fileName);

		const int dataLenght = 10;
		const int dataSize = dataLenght * sizeof(unsigned char);
		auto data = LFMemoryManager::NewArray<unsigned char>(INFO, dataLenght);
		for (int i = 0; i < dataLenght; ++i)
			data[i] = i;

		LFSerializer<unsigned char> ser;
		ser.WriteDynamicBinaryData(LFVFSPath::DataReadWrite, fileName, data, dataSize);
		LFMemoryManager::DeleteArray(data);

		auto data2 = LFMemoryManager::NewArray<unsigned char>(INFO, dataLenght);
		ser.ReadDynamicBinaryData(LFVFSPath::DataReadWrite, fileName, data2, dataSize);

		int matches = 0;
		for (int i = 0; i < dataLenght; ++i)
			if (data2[i] == i)
				matches++;

		LFMemoryManager::DeleteArray(data2);

		LFTest::AssertOk(LFFile::IsFileExist(LFVFSPath::DataReadWrite, fileName), INFO);
		LFTest::AssertOk(matches == dataLenght, INFO);

		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, fileName))
			LFFile::Delete(LFVFSPath::DataReadWrite, fileName);

		LFIoc<LFVFSManager *>::Release();
	}

	void LFIOTest::LFTextRWTest()
	{
		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();

		LFTextRW textRW;
		LFString testFileName(LFIoc<LFVFSManager *>::Get()->GetPath(LFVFSPath::DataRead));
		testFileName += "ReadTest.txt";

		LFString testText = textRW.Read(testFileName);
#ifdef TIZEN
		testText.Remove('\r');
#endif
		auto test = LFString("Lightfield3 Engine\nText read test\n");
		LFTest::AssertOk(testText == test, INFO);

		LFIoc<LFVFSManager *>::Release();
	}

	void LFIOTest::LFLoggerTest()
	{
		#ifdef WINCLASSIC
			if (LFFile::IsFileExist(LFVFSPath::No, LFIoc<LFLogger>::Get().LogFileName))
				LFFile::Delete(LFVFSPath::No, LFIoc<LFLogger>::Get().LogFileName);

			LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToFile, true);
		#endif

		LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToBuffer, true);
		LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToLogTrigger, true);

		LFString testLog("Test log...");
		LFString triggeredLog;
		LFIoc<LFLogger>::Get().SetLogTrigger([&triggeredLog](const LFString &log) { triggeredLog += log; });

		LFIoc<LFLogger>::Get().WriteOutput(testLog);
		
		#ifdef WINCLASSIC
			LFTest::AssertOk(LFFile::IsFileExist(LFVFSPath::No, LFIoc<LFLogger>::Get().LogFileName), INFO);
		#endif

		LFTest::AssertOk(LFIoc<LFLogger>::Get().GetBuffer()->GetExistCount(testLog) == 1, INFO);
		LFTest::AssertOk(triggeredLog.GetExistCount(testLog) == 1, INFO);

		LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToBuffer, false);
		LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToLogTrigger, false);

		#ifdef WINCLASSIC
			LFIoc<LFLogger>::Get().SetOutputTypeFlag(LFLogOutputType::ToFile, false);

			if (LFFile::IsFileExist(LFVFSPath::No, LFIoc<LFLogger>::Get().LogFileName))
				LFFile::Delete(LFVFSPath::No, LFIoc<LFLogger>::Get().LogFileName);
		#endif
	}

	void LFIOTest::LFJsonTest()
	{
		/*example: request select Solar10 hiscore list
		{
			"DbUser": "user",
			"DbPasswd": "jlj545l45k4l",
			"GameName": "Solar10"
		}
		*/
		LFList<LFJSonPair> pairs;
		pairs.Add({ LFString("DbUser"), LFString("user") });
		pairs.Add({ LFString("DbPasswd"), LFString("jlj545l45k4l") });
		pairs.Add({ LFString("GameName"), LFString("Solar10") });
		LFTest::AssertOk(LFJson::CreateObjectPairs(pairs) == LFString("{\"DbUser\":\"user\",\"DbPasswd\":\"jlj545l45k4l\",\"GameName\":\"Solar10\"}"), INFO);

		/*example: response after update/insert player's score
		{
			"rank": "512"
		}
		*/
		auto pair = LFJson::GetObjectPair(LFString("{\"rank\":\"512\"}"));
		LFTest::AssertOk(pair.key == LFString("rank"), INFO);
		LFTest::AssertOk(pair.value == LFString("512"), INFO);

		auto pair2 = LFJson::GetObjectPair(LFString("error"));
		LFTest::AssertOk(pair2.key != LFString("error"), INFO);
		LFTest::AssertOk(pair2.value != LFString("error"), INFO);

		/*example: response select Solar10 hiscore list
		[
			{
				"PlayerName": "Master1",
				"Level": 122,
				"Score": 1200
			},
			{				
				"PlayerName": "Master2",
				"Level": 322,
				"Score": 1500
			}
		]
		*/
		auto hiscoreList = LFJson::GetArrayPairs(LFString("[{\"PlayerName\":\"Master1\",\"Level\":\"122\",\"Score\":\"1200\"},{\"PlayerName\":\"Master2\",\"Level\":\"322\",\"Score\":\"1500\"}]"));
		bool isHiscoreListOk = hiscoreList.GetLength() == 2 && hiscoreList[0].GetLength() == 3 && hiscoreList[1].GetLength() == 3;
		LFTest::AssertOk(isHiscoreListOk, INFO);

		if (isHiscoreListOk)
		{
			LFTest::AssertOk(hiscoreList[0][0].key == LFString("PlayerName"), INFO);
			LFTest::AssertOk(hiscoreList[0][0].value == LFString("Master1"), INFO);
			LFTest::AssertOk(hiscoreList[0][1].key == LFString("Level"), INFO);
			LFTest::AssertOk(hiscoreList[0][1].value == LFString("122"), INFO);
			LFTest::AssertOk(hiscoreList[0][2].key == LFString("Score"), INFO);
			LFTest::AssertOk(hiscoreList[0][2].value == LFString("1200"), INFO);
			
			LFTest::AssertOk(hiscoreList[1][0].key == LFString("PlayerName"), INFO);
			LFTest::AssertOk(hiscoreList[1][0].value == LFString("Master2"), INFO);
			LFTest::AssertOk(hiscoreList[1][1].key == LFString("Level"), INFO);
			LFTest::AssertOk(hiscoreList[1][1].value == LFString("322"), INFO);
			LFTest::AssertOk(hiscoreList[1][2].key == LFString("Score"), INFO);
			LFTest::AssertOk(hiscoreList[1][2].value == LFString("1500"), INFO);
		}
	}

	void LFIOTest::RunAllTests()
	{
		LFSerializerStaticBinaryTest();
		LFSerializerDynamicBinaryTest();
		LFTextRWTest();
		LFLoggerTest();
		LFJsonTest();
	}
}}}}
