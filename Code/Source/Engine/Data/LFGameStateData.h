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
	#define GameStateDataName "GameStateData" LFDataExtension

	class LFENGINE_LIBRARY LFGameStateData : public LFIData
	{ 
	public:
		struct Data
		{
			unsigned char id;

			//data for game
			unsigned char levelIndex; //LF/Snake: current level index
			unsigned short second; //LF: current game time seconds / Snake: eggs
			unsigned short lives; //Snake: lives

			//current level
			//example: levelMatrix[0][0] = 12; The first element in this level represents x = 1, y = 2 atlas tile
			unsigned char levelMatrix[LFDataMaxLevelSize][LFDataMaxLevelSize];
			
			EditorData editorData;

			Data() : id(0)
			{ }
		};
		
	private:
		LFCore::IO::LFSerializer<Data> serializer;

	public:
		Data data;

		LFGameStateData();
		~LFGameStateData() override { };

		void Reset() override;
		bool Load() override; //open from VFS
		bool Load(const char *fileName) override; //open from file somwhere
		void Save() override; //save to VFS
		void Save(const char *fileName) override; //save to file somwhere
	};
}}
