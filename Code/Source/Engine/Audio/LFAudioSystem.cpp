/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFAudioSystem.h"
#include "..\..\Core\Common\LFString.h"
#include "..\..\Core\\IO\LFLogger.h"
#include "..\Common\LFSystemInfo.h"

using namespace LFCore::Common;
using namespace LFCore::IO;
using namespace LFEngine::Common;

namespace LFEngine { namespace Audio
{
	LFAudioSystem *LFAudioSystem::instance = nullptr;

	LFAudioSystem::LFAudioSystem() : isMusicOn(false), isSFXOn(false), volumeMusic(0), volumeSFX(0)
	{ 
		LFLogger::Instance().WriteOutput("Create AudioSystem");
	}

	LFAudioSystem::~LFAudioSystem()
	{ 
		LFLogger::Instance().WriteOutput("Release AudioSystem");
	}

	bool LFAudioSystem::IsSilentMode()
	{
		return LFSystemInfo::IsSilentMode();
	}

	void LFAudioSystem::VolumeOn(const char *channel, bool isOn)
	{
		if (LFString::IsEqual(channel, CHMusic))
			isMusicOn = isOn;
		else if (LFString::IsEqual(channel, CHSfx))
			isSFXOn = isOn;
	}

	bool LFAudioSystem::VolumeOn(const char *channel)
	{
		bool result = false;

		if (LFString::IsEqual(channel, CHMusic))
			result = isMusicOn;
		else if (LFString::IsEqual(channel, CHSfx))
			result = isSFXOn; 

		return result;
	}

	void LFAudioSystem::Volume(const char *channel, int volume)
	{
		if (LFString::IsEqual(channel, CHMusic))
			volumeMusic = volume;
		else if (LFString::IsEqual(channel, CHSfx))
			volumeSFX = volume;
	}

	int LFAudioSystem::Volume(const char *channel)
	{
		int result = 0;

		if (LFString::IsEqual(channel, CHMusic))
			result = volumeMusic;
		else if (LFString::IsEqual(channel, CHSfx))
			result = volumeSFX;

		return result;
	}
}}
