/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFIData.h"
#include "..\LFCore\LFIO\LFSerializer.h"

namespace LF3Engine { namespace LFEngine { namespace LFData
{
	/**
		@brief
		Options data (read and write for game) <br>
	*/
	class LFOptionsData final : public LFIData
	{ 
	public:
		struct Data
		{
			unsigned char id;
			bool isMusicOn, isSFXOn;
			float volumeMusic, volumeSFX;
			char playerName[20];
			char phoneId[20];

			Data() : id(0), isMusicOn(false), isSFXOn(false), volumeMusic(0), volumeSFX(0), playerName{}, phoneId{}
			{ }
		};
		
	private:
		LFCore::LFIO::LFSerializer<Data> serializer;

	public:
		Data data;

		LFOptionsData();
		~LFOptionsData() = default;

		//LFIData functions
		void Reset() override;
		bool Load() override; //open from VFS
		bool Load(const char *fileName) override; //open from file somwhere
		void Save() override; //save to VFS
		void Save(const char *fileName) override; //save to file somwhere
	};
}}}
