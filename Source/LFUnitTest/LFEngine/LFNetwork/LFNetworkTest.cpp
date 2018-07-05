/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFNetworkTest.h"
#include "..\..\LFTest.h"
#include "..\..\..\LFEngine\LFNetwork\LFCurl.h"
#include "..\..\..\LFEngine\LFCore\LFCommon\LFSystemData.h"
#include "..\..\..\LFEngine\LFCore\LFIO\LFJson.h"

using namespace LF3Engine::LFEngine::LFNetwork;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFCollections;
using namespace LF3Engine::LFEngine::LFCore::LFIO;

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFNetwork
{
	void LFNetworkTest::LFCurlBasicTest()
	{
		/*const LFString testResponse("test response");
		LFList<LFJSonPair> jsonRequestPairs;
		jsonRequestPairs.Add({ LFString(LFSystemData::LFDbCommandKey), testResponse });

		auto jsonResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonRequestPairs));
		auto jsonResponsePair = LFJson::GetObjectPair(jsonResponse);
		LFTest::AssertOk(jsonResponsePair.key == LFString(LFSystemData::LFDbCommandKey), INFO);
		LFTest::AssertOk(jsonResponsePair.value == testResponse, INFO);

		auto wrongJsonResponse = LFCurl::GetResponse("http://4dillusions.com/Page/Hiscore/WrongJsonTest.php?", LFJson::CreateObjectPairs(jsonRequestPairs));
		auto wrongJsonResponsePair = LFJson::GetObjectPair(wrongJsonResponse);
		LFTest::AssertOk(wrongJsonResponsePair.key == LFString(""), INFO);
		LFTest::AssertOk(wrongJsonResponsePair.value == LFString(""), INFO);

		LFList<LFJSonPair> wrongJsonRequestPairs;
		wrongJsonRequestPairs.Add({ LFString("wrongIndex"), testResponse });
		auto wrongJsonResponse2 = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(wrongJsonRequestPairs));
		auto wrongJsonResponsePair2 = LFJson::GetObjectPair(wrongJsonResponse2);
		LFTest::AssertOk(wrongJsonResponsePair2.key == LFString(LFSystemData::LFDbCommandKey), INFO);
		LFTest::AssertOk(wrongJsonResponsePair2.value != testResponse, INFO);*/
	}

	void LFNetworkTest::LFCurlMySQLTest()
	{
		//{"Command":"Delete","DbUser":"LF3Gamer","DbPasswd":"Sekure459vB62","GameName":"TestGame","PhoneId":"All"}
		//delete all
		/*LFList<LFJSonPair> jsonDeletePairs;
		jsonDeletePairs.Add({ LFString(LFSystemData::LFDbCommandKey), LFString("Delete") });
		jsonDeletePairs.Add({ LFString("DbUser"), LFString(LFSystemData::LFDbUser) });
		jsonDeletePairs.Add({ LFString("DbPasswd"), LFString(LFSystemData::LFDbPasswd) });
		jsonDeletePairs.Add({ LFString("GameName"), LFString("TestGame") });
		jsonDeletePairs.Add({ LFString("PhoneId"), LFString("All") });
		LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonDeletePairs));*/

		//{"Command":"InsertUpdate","DbUser":"LF3Gamer","DbPasswd":"Sekure459vB62","GameName":"TestGame","PhoneId":"1234","PlayerName":"Name23","Score":"1252","Level":"122"}
		/*LFList<LFJSonPair> jsonInsertPairs;
		jsonInsertPairs.Add({ LFString(LFSystemData::LFDbCommandKey), LFString(LFSystemData::LFDbInsertUpdateHiscoreCommand) });
		jsonInsertPairs.Add({ LFString("DbUser"), LFString(LFSystemData::LFDbUser) });
		jsonInsertPairs.Add({ LFString("DbPasswd"), LFString(LFSystemData::LFDbPasswd) });
		jsonInsertPairs.Add({ LFString("GameName"), LFString("TestGame") });

		jsonInsertPairs.Add({ LFString("PhoneId"), LFString("1234") });
		jsonInsertPairs.Add({ LFString("PlayerName"), LFString("Player 1") });
		jsonInsertPairs.Add({ LFString("Score"), LFString("1234") });
		jsonInsertPairs.Add({ LFString("Level"), LFString("12") });*/

		//insert 1
		/*auto jsonResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonInsertPairs));
		auto jsonResponsePair = LFJson::GetObjectPair(jsonResponse);
		LFTest::AssertOk(jsonResponsePair.key == LFString("Rank"), INFO);
		LFTest::AssertOk(jsonResponsePair.value == LFString("1"), INFO);*/

		//insert with already PlayerName
		/*jsonInsertPairs[4].value = LFString("12345");
		jsonInsertPairs[6].value = LFString("8500");
		jsonInsertPairs[7].value = LFString("85");
		jsonResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonInsertPairs));
		jsonResponsePair = LFJson::GetObjectPair(jsonResponse);
		LFTest::AssertOk(jsonResponsePair.key == LFString("Rank"), INFO);
		LFTest::AssertOk(jsonResponsePair.value == LFString("-2"), INFO);*/

		//insert 2
		/*jsonInsertPairs[5].value = LFString("Player2");
		jsonResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonInsertPairs));
		jsonResponsePair = LFJson::GetObjectPair(jsonResponse);
		LFTest::AssertOk(jsonResponsePair.key == LFString("Rank"), INFO);
		LFTest::AssertOk(jsonResponsePair.value == LFString("1"), INFO);*/

		//insert 3
		/*jsonInsertPairs[4].value = LFString("123456");
		jsonInsertPairs[5].value = LFString("Player 3");
		jsonInsertPairs[6].value = LFString("3500");
		jsonInsertPairs[7].value = LFString("35");
		auto jsonResponse3 = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonInsertPairs));
		auto jsonResponsePair3 = LFJson::GetObjectPair(jsonResponse3);
		LFTest::AssertOk(jsonResponsePair3.key == LFString("Rank"), INFO);
		LFTest::AssertOk(jsonResponsePair3.value == LFString("2"), INFO);*/

		//update player 3 with already PlayerName
		/*jsonInsertPairs[5].value = LFString("Player2");
		jsonInsertPairs[6].value = LFString("9500");
		jsonInsertPairs[7].value = LFString("95");
		jsonResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonInsertPairs));
		jsonResponsePair = LFJson::GetObjectPair(jsonResponse);
		LFTest::AssertOk(jsonResponsePair.key == LFString("Rank"), INFO);
		LFTest::AssertOk(jsonResponsePair.value == LFString("-2"), INFO);*/

		//update player 3 wrong score
		/*jsonInsertPairs[5].value = LFString("Player 3");
		jsonInsertPairs[6].value = LFString("500");
		jsonInsertPairs[7].value = LFString("5");
		jsonResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonInsertPairs));
		jsonResponsePair = LFJson::GetObjectPair(jsonResponse);
		LFTest::AssertOk(jsonResponsePair.key == LFString("Rank"), INFO);
		LFTest::AssertOk(jsonResponsePair.value == LFString("-1"), INFO);*/

		//update player 3
		/*jsonInsertPairs[6].value = LFString("3700");
		jsonInsertPairs[7].value = LFString("37");
		jsonResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonInsertPairs));
		jsonResponsePair = LFJson::GetObjectPair(jsonResponse);
		LFTest::AssertOk(jsonResponsePair.key == LFString("Rank"), INFO);
		LFTest::AssertOk(jsonResponsePair.value == LFString("2"), INFO);*/

		//{"Command":"Select","DbUser":"LF3Gamer","DbPasswd":"Sekure459vB62","GameName":"TestGame"}
		//select
		/*LFList<LFJSonPair> jsonSelectPairs;
		jsonSelectPairs.Add({ LFString(LFSystemData::LFDbCommandKey), LFString(LFSystemData::LFDbSelectHiscoreCommand) });
		jsonSelectPairs.Add({ LFString("DbUser"), LFString(LFSystemData::LFDbUser) });
		jsonSelectPairs.Add({ LFString("DbPasswd"), LFString(LFSystemData::LFDbPasswd) });
		jsonSelectPairs.Add({ LFString("GameName"), LFString("TestGame") });
		auto jsonSelectResponse = LFCurl::GetResponse(LFSystemData::LFServerTestURL, LFJson::CreateObjectPairs(jsonSelectPairs));
		auto jsonSelectResponsePairs = LFJson::GetArrayPairs(jsonSelectResponse);
		
		bool isItemsCountOk = jsonSelectResponsePairs.GetLength() == 3;
		LFTest::AssertOk(isItemsCountOk, INFO);
		if (isItemsCountOk)
		{
			LFTest::AssertOk(jsonSelectResponsePairs[0][0].value == LFString("Player 1"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[0][1].value == LFString("12"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[0][2].value == LFString("1234"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[1][0].value == LFString("Player2"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[1][1].value == LFString("85"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[1][2].value == LFString("8500"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[2][0].value == LFString("Player 3"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[2][1].value == LFString("37"), INFO);
			LFTest::AssertOk(jsonSelectResponsePairs[2][2].value == LFString("3700"), INFO);
		}*/
	}

	void LFNetworkTest::RunAllTests()
	{
		LFCurlBasicTest();
		LFCurlMySQLTest();
	}
}}}}
