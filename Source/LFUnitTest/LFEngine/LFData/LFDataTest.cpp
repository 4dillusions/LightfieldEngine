/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFDataTest.h"
#include "..\..\LFTest.h"
#include "..\..\..\LFEngine\LFCore\LFIO\LFSerializer.h"
#include "..\..\..\LFEngine\LFCore\LFIO\LFFile.h"
#include "..\..\..\LFEngine\LFData\LFOptionsdata.h"
#include "..\..\..\LFEngine\LFData\LFGameStatedata.h"
#include "..\..\..\LFEngine\LFData\LFLeveldata.h"

using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFData;

namespace LF3Engine { namespace LFUnitTest { namespace LFEngine { namespace LFData
{
	void LFDataTest::LFGameStateTest()
	{
		//read and write test
		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();
	
		LFGameStateData *data;
	
		//save
		data = LFMemoryManager::New<LFGameStateData>(INFO);
		//LFSystemData::LFGameStateDataId
		data->data.levelIndexArcade = 10;
		data->data.levelIndexPuzzle = 1600;
		data->data.second = 20;
		data->data.lives = 3;
		data->data.scoreArcade = 300;
		data->data.scorePuzzle = 25000000;
		data->data.rank = 19;
		
		data->data.editorData.levelSizeX = 30;
		data->data.editorData.levelSizeY = 43;
		data->data.editorData.tilesId = 2;
		data->data.editorData.zoom = 8;
	
		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, LFSystemData::LFGameStateDataName))
			LFFile::Delete(LFVFSPath::DataReadWrite, LFSystemData::LFGameStateDataName);
	
		data->Save(); //data->Save("d:\\GameStateData.dat");
		LFMemoryManager::Delete(data);
	
		//load
		data = LFMemoryManager::New<LFGameStateData>(INFO);
		LFTest::AssertOk(data->Load(), INFO);
		LFTest::AssertOk(data->data.id == LFSystemData::LFGameStateDataId && data->data.levelIndexArcade == 10 && data->data.levelIndexPuzzle == 1600 && 
			data->data.second == 20 && data->data.lives == 3 && data->data.scoreArcade == 300 && data->data.scorePuzzle == 25000000 &&
			data->data.rank == 19 && data->data.editorData.levelSizeX == 30 &&
			data->data.editorData.levelSizeY == 43 && data->data.editorData.tilesId == 2 && data->data.editorData.zoom == 8, INFO);
		LFMemoryManager::Delete(data);
	
		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, LFSystemData::LFGameStateDataName))
			LFFile::Delete(LFVFSPath::DataReadWrite, LFSystemData::LFGameStateDataName);
	
		LFIoc<LFVFSManager *>::Release();
	}
	
	void LFDataTest::LFLevelDataTest()
	{
		//read only for game test
		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();
	
		const int levelDataIndex = 5;

		//save for testing: create LevelData on Windows
		#ifdef WINCLASSIC
			LFLevelData *dataSave = LFMemoryManager::New<LFLevelData>(INFO);
		
			dataSave->data.levelCount = 10;
			dataSave->data.levelMatrix[0][0][0] = 1;
			dataSave->data.levelMatrix[9][20][10] = 3;
			dataSave->data.editorData.levelSizeX = 30;
			dataSave->data.editorData.levelSizeY = 43;
			dataSave->data.editorData.tilesId = 2;
			dataSave->data.editorData.zoom = 8;
	
			dataSave->Save(levelDataIndex); //dataSave->Save("d:\\LevelData5.dat");
			LFMemoryManager::Delete(dataSave);
		#endif

		//load
		LFLevelData *data = LFMemoryManager::New<LFLevelData>(INFO);
		LFTest::AssertOk(data->Load(levelDataIndex), INFO); //LFTest::AssertOk(data->Load("d:\\LevelData5.dat"), INFO);
		LFTest::AssertOk(data->data.id == LFSystemData::LFLevelDataId && data->data.levelCount == 10 &&
			data->data.levelMatrix[0][0][0] == 1 && data->data.levelMatrix[9][20][10] == 3 && data->data.editorData.levelSizeX == 30 && 
			data->data.editorData.levelSizeY == 43 && data->data.editorData.tilesId == 2 && data->data.editorData.zoom == 8, INFO);
		LFMemoryManager::Delete(data);

		#ifdef WINCLASSIC
			LFString fileName(LFSystemData::LFLevelDataName);
			if (levelDataIndex >= 0)
				fileName.Replace(LFString("."), LFString(levelDataIndex) + ".");

			if (LFFile::IsFileExist(LFVFSPath::DataRead, fileName.ToChar()))
				LFFile::Delete(LFVFSPath::DataRead, fileName.ToChar());
		#endif
	
		LFIoc<LFVFSManager *>::Release();
	}
	
	void LFDataTest::LFOptionsDataTest()
	{
		//read and write test
		LFIoc<LFVFSManager *>::Register<LFVFSManager>();
		LFIoc<LFVFSManager *>::Create();
	
		LFOptionsData *data;
	
		//save
		data = LFMemoryManager::New<LFOptionsData>(INFO);
		//LFSystemData::LFOptionsDataId
		data->data.isMusicOn = false;
		data->data.isSFXOn = true;
		data->data.volumeMusic = 0.2f;
		data->data.volumeSFX = 0.9f;
		LFString::CopyToArray("Player12", data->data.playerName);
		LFString::CopyToArray("20140908175104777", data->data.phoneId);
	
		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, LFSystemData::LFOptionsDataName))
			LFFile::Delete(LFVFSPath::DataReadWrite, LFSystemData::LFOptionsDataName);
	
		data->Save();
		LFMemoryManager::Delete(data);
	
		//load
		data = LFMemoryManager::New<LFOptionsData>(INFO);
		LFTest::AssertOk(data->Load(), INFO);
		LFTest::AssertOk(data->data.id == LFSystemData::LFOptionsDataId && !data->data.isMusicOn && data->data.isSFXOn && data->data.volumeMusic == 0.2f && data->data.volumeSFX == 0.9f && 
			LFString(data->data.playerName) == LFString("Player12") && LFString(data->data.phoneId) == LFString("20140908175104777"), INFO);
		LFMemoryManager::Delete(data);
	
		if (LFFile::IsFileExist(LFVFSPath::DataReadWrite, LFSystemData::LFOptionsDataName))
			LFFile::Delete(LFVFSPath::DataReadWrite, LFSystemData::LFOptionsDataName);
	
		LFIoc<LFVFSManager *>::Release();
	}
	
	void LFDataTest::RunAllTests()
	{
		LFGameStateTest();
		LFLevelDataTest();
		LFOptionsDataTest();
	}
}}}}
