/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFAudioSystem.h"
#include "..\LFCore\LFPatterns\LFIoc.h"
#include "..\LFCore\LFIO\LFLogger.h"
#include "..\LFCore\LFCommon\LFSystemData.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;

namespace LF3Engine { namespace LFEngine { namespace LFAudio
{
	LFAudioSystem *LFAudioSystem::audio = nullptr;

	LFAudioSystem::LFAudioSystem() : isMusicOn(false), isSFXOn(false), volumeMusic(0.0f), volumeSFX(0.0f), vfsManager(nullptr)
	{
		LFIoc<LFLogger>::Get().WriteOutput("Create AudioSystem");
		vfsManager = LFIoc<LFVFSManager *>::Get();
	}

	LFAudioSystem::~LFAudioSystem()
	{
		LFIoc<LFLogger>::Get().WriteOutput("Release AudioSystem");
	}

	bool LFAudioSystem::IsSilentMode()
	{
		return LFSystemData::GetIsSilentMode();
	}

	void LFAudioSystem::SetIsVolumeOnSfx(bool isOn)
	{
		isSFXOn = isOn;
	}

	void LFAudioSystem::SetIsVolumeOnMusic(bool isOn)
	{
		isMusicOn = isOn;
	}

	bool LFAudioSystem::GetIsVolumeOnSfx() const
	{
		return isSFXOn;
	}

	bool LFAudioSystem::GetIsVolumeOnMusic() const
	{
		return isMusicOn;
	}

	float LFAudioSystem::GetVolumeSfx() const
	{
		return volumeSFX;
	}

	float LFAudioSystem::GetVolumeMusic() const
	{
		return volumeMusic;
	}

	void LFAudioSystem::SetVolumeSfx(float volume)
	{
		volumeSFX = volume;
	}

	void LFAudioSystem::SetVolumeMusic(float volume)
	{
		volumeMusic = volume;
	}
}}}
