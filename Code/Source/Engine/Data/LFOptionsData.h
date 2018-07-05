/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "LFIData.h"
#include "..\Common\LFExtensions.h"
#include "..\..\Core\\IO\LFSerializer.h"

namespace LFEngine { namespace Data
{
	#define OptionsDataName "OptionsData" LFDataExtension

	class LFENGINE_LIBRARY LFOptionsData : public LFIData
	{ 
	public:
		struct Data
		{
			unsigned char id;
			bool isMusicOn, isSFXOn;
			unsigned char volumeMusic, volumeSFX;

			Data() : id(0)
			{ }
		};
		
	private:
		LFCore::IO::LFSerializer<Data> serializer;

	public:
		Data data;

		LFOptionsData();
		~LFOptionsData() override { };

		void Reset() override;
		bool Load() override; //open from VFS
		bool Load(const char *fileName) override; //open from file somwhere
		void Save() override; //save to VFS
		void Save(const char *fileName) override; //save to file somwhere
	};
}}
