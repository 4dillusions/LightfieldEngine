/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFIData.h"
#include "LFEditorData.h"
#include "..\LFCore\LFIO\LFSerializer.h"

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	#define GameStateDataName "GameStateData" LFDataExtension

	/**
		@brief
		GameState data (read and write for game) <br>
	*/
	class LFGameStateData : public LFIData
	{ 
	public:
		struct Data
		{
			unsigned char id;

			//data for game
			unsigned int levelIndexPuzzle;
			unsigned int levelIndexArcade;
			unsigned short second;
			unsigned short lives;
			unsigned int scorePuzzle;
			unsigned int scoreArcade;
			unsigned int rank;

			//editor
			LFEditorData editorData;

			Data() : id(0), levelIndexPuzzle(0), levelIndexArcade(0), second(0), lives(0), scorePuzzle(0), scoreArcade(0), rank(0), editorData()
			{ }
		};
		
	private:
		LFCore::LFIO::LFSerializer<Data> serializer;

	public:
		Data data;

		LFGameStateData();
		~LFGameStateData() = default;

		//LFIData functions
		void Reset() override;
		bool Load() override; //open from VFS
		bool Load(const char *fileName) override; //open from file somwhere
		void Save() override; //save to VFS
		void Save(const char *fileName) override; //save to file somwhere
	};
}}}
