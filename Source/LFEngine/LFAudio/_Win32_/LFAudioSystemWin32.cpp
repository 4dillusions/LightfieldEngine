/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#include "LFAudioSystemWin32.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\LFCore\LFCommon\LFVFSManager.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;
using namespace audiere;

namespace LF3Engine { namespace LFEngine { namespace LFAudio
{
	LFAudioSystemWin32::LFAudioSystemWin32() : audioDevice(nullptr), sfxStream(nullptr), musicStream(nullptr), musicStreamPosition(0)
	{
		audioDevice = OpenDevice(nullptr);
	}

	void LFAudioSystemWin32::SetVolumeSfx(float volume)
	{
		LFAudioSystem::SetVolumeSfx(volume);

		if (sfxStream)
			sfxStream->setVolume(volume);
	}

	void LFAudioSystemWin32::SetVolumeMusic(float volume)
	{
		LFAudioSystem::SetVolumeMusic(volume);

		if (musicStream)
			musicStream->setVolume(volume);
	}

	void LFAudioSystemWin32::PlaySfx(const char *soundName)
	{
		LFString soundFullName(vfsManager->GetPath(LFVFSPath::Sound));
		soundFullName += soundName;

		if (!IsSilentMode() && isSFXOn)
		{
			sfxStream = OpenSound(audioDevice, soundFullName.ToChar(), true);

			if (sfxStream)
			{
				sfxStream->setVolume(volumeSFX);
				sfxStream->setRepeat(false);
				sfxStream->play();
			}
			else
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, soundFullName);
		}
	}

	void LFAudioSystemWin32::PlayMusic(const char *soundName)
	{
		LFString soundFullName(vfsManager->GetPath(LFVFSPath::Sound));
		soundFullName += soundName;

		if (!IsSilentMode() && isMusicOn)
		{
			musicStreamPosition = 0;
			musicStream = OpenSound(audioDevice, soundFullName.ToChar(), true);

			if (musicStream)
			{
				musicStream->setVolume(volumeMusic);
				musicStream->setRepeat(true);
				musicStream->play();
			}
			else
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, soundFullName);
		}
	}

	void LFAudioSystemWin32::PauseMusic()
	{
		if (musicStream)
		{
			musicStreamPosition = musicStream->getPosition();
			musicStream->stop();
		}
	}

	void LFAudioSystemWin32::ContinueMusic()
	{
		if (isMusicOn && !IsSilentMode() && musicStream && musicStreamPosition > 0)
		{
			musicStream->setVolume(volumeMusic);
			musicStream->setRepeat(true);
			musicStream->setPosition(musicStreamPosition);
			musicStream->play();
		}
	}

	void LFAudioSystemWin32::StopSfx()
	{
		if (sfxStream)
			sfxStream->stop();
	}

	void LFAudioSystemWin32::StopMusic()
	{
		musicStreamPosition = 0;

		if (musicStream)
			musicStream->stop();
	}
}}}

#endif
