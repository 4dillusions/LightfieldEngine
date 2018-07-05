/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFJson.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFCollections;

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFIO 
{
	LFString LFJson::CreateObjectPairs(LFList<LFJSonPair> &pairs)
	{
		LFString result("{"); //xample: {"DbUser":"user","DbPasswd":"jlj545l45k4l","GameName":"Solar10"}

		for (pairs.First(); pairs.IsDone(); pairs.Next())
			result += LFString("\"") + pairs.GetCurrent().key + "\":\"" + pairs.GetCurrent().value + "\",";

		result.Remove(result.GetTextLength() - 1, 1);
		result += "}";
		
		return result;
	}

	LFJSonPair LFJson::GetObjectPair(const LFString &jsonPair)
	{
		LFString result1, result2;
		LFString tempJsonPair(jsonPair);

		//xample: {"rank":"512"} -> rank#512
		tempJsonPair.Replace(LFString("{\""), LFString(""));
		tempJsonPair.Replace(LFString("\"}"), LFString(""));
		tempJsonPair.Replace(LFString("\":\""), LFString("#"));
		auto pairList = tempJsonPair.Split('#');
		if (pairList.GetLength() == 2)
		{
			result1 = pairList[0];
			result2 = pairList[1];
		}

		return { result1, result2 };
	}

	LFList<LFList<LFJSonPair>> LFJson::GetArrayPairs(const LFString &jsonArray)
	{
		LFList<LFList<LFJSonPair>> result;
		LFString tempJsonArray(jsonArray);
		
		//[{"PlayerName":"Master1","Score":"1200"},{"PlayerName":"Master2","Score":"1500"}] -> "PlayerName":"Master1","Score":"1200"#"PlayerName":"Master2","Score":"1500"
		tempJsonArray.Replace(LFString("[{"), LFString(""));
		tempJsonArray.Replace(LFString("}]"), LFString(""));
		tempJsonArray.Replace(LFString("},{"), LFString("#"));

		auto objectList = tempJsonArray.Split('#'); //"PlayerName":"Master1","Score":"1200" ... "PlayerName":"Master2","Score":"1500"
		for (objectList.First(); objectList.IsDone(); objectList.Next())
		{
			result.Add(LFList<LFJSonPair>());

			//"PlayerName":"Master1","Score":"1200" -> PlayerName:Master1#Score:1200
			LFString tempObject(objectList.GetCurrent());
			tempObject.Replace(LFString("\""), LFString(""));
			tempObject.Replace(LFString(','), LFString('#'));

			auto pairList = tempObject.Split('#'); //PlayerName:Master1 ... Score:1200
			for (pairList.First(); pairList.IsDone(); pairList.Next())
			{
				LFString tempPair(pairList.GetCurrent());
				auto memberList = tempPair.Split(':');
				if (memberList.GetLength() == 2)
					result[result.GetLength() - 1].Add({ memberList[0], memberList[1] }); //PlayerName:Master1
			}
		}

		return result;
	}
}}}}
