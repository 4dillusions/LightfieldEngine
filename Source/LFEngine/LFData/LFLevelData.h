/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFIData.h"
#include "LFEditorData.h"
#include "..\LFCore\LFIO\LFSerializer.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	/**
		@brief
		Level data (read only for game) <br>
	*/
	class LFLevelData final : public LFIData
	{ 	
	public:
		struct Data
		{
			unsigned char id;

			//data for game
			unsigned char levelCount; //how many levels are there

			//all levels
			//example: levelMatrix[12][0][0] = 45; The first element in 12. level represents x = 4, y = 5 atlas tile
			unsigned char levelMatrix[LFSystemData::LFDataMaxLevelCount][LFSystemData::LFDataMaxLevelSize][LFSystemData::LFDataMaxLevelSize];

			LFEditorData editorData;

			Data() : id(0), levelCount(0), levelMatrix{}, editorData()
			{ }
		};

	private:
		LFCore::LFIO::LFSerializer<Data> serializer;
		
	public:
		Data data;

		LFLevelData();
		~LFLevelData() = default;

		bool Load(int fileIndex); //open from VFS example: index = 0, load <levelName>0.<extension> levelCount levels
		void Save(int fileIndex); //save to VFS example: index = 0, save <levelName>0.<extension> levelCount levels

		//LFIData functions
		void Reset() override;
		bool Load() override; //open from VFS
		bool Load(const char *fileName) override; //open from file somwhere
		void Save() override; //save to VFS
		void Save(const char *fileName) override; //save to file somwhere
	};

	struct LevelMatrixData
	{
		unsigned char levelMatrix[LFSystemData::LFDataMaxLevelSize][LFSystemData::LFDataMaxLevelSize];

		LevelMatrixData() : levelMatrix{}
		{ }
	};
}}}
