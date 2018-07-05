/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFIData.h"
#include "LFEditorData.h"
#include "..\Common\LFExtensions.h"
#include "LFDataConstants.h"
#include "..\..\Core\IO\LFSerializer.h"

namespace LFEngine { namespace Data
{
	#define LevelDataName "LevelData" LFDataExtension

	class LFENGINE_LIBRARY LFLevelData : public LFIData
	{ 
	public:
		struct Data
		{
			unsigned char id;

			//data for game
			unsigned char levelCount; //how many levels are there

			//all levels
			//example: levelMatrix[12][0][0] = 45; The first element in 12. level represents x = 4, y = 5 atlas tile
			unsigned char levelMatrix[LFDataMaxLevelCount][LFDataMaxLevelSize][LFDataMaxLevelSize];

			EditorData editorData;
		};
		
	private:
		LFCore::IO::LFSerializer<Data> serializer;

	public:
		Data data;

		LFLevelData();
		~LFLevelData() override { };

		void Reset() override;
		bool Load() override; //open from VFS
		bool Load(const char *fileName) override; //open from file somwhere
		void Save() override; //save to VFS
		void Save(const char *fileName) override; //save to file somwhere
	};
}}
