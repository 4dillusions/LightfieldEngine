/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LFAudioSystemAudiere.h"
#include "..\..\..\Core\Common\LFMemoryManager.h"
#include "..\..\..\Core\Common\LFString.h"
#include "..\..\..\Core\Common\LFVFSManager.h"
#include "..\..\..\Core\IO\LFLogger.h"

using namespace LFCore::Common;
using namespace LFCore::IO;

namespace LFEngine { namespace Audio
{
	LFAudioSystemAudiere::LFAudioSystemAudiere() : musicStreamPosition(0)
	{
		audioDevice = audiere::OpenDevice(nullptr);
	}

	void LFAudioSystemAudiere::CreateInstance()
	{
		if (instance == nullptr)
			instance = LFNew<LFAudioSystemAudiere>(AT);
	}

	void LFAudioSystemAudiere::ReleaseInstance()
	{
		if (instance != nullptr)
			LFDelete(instance);
	}

	void LFAudioSystemAudiere::Volume(const char *channel, int volume)
	{
		//convert 1-100 to 0-99
		if (volume < 0)
			volume = 0;

		if (volume > 99)
			volume = 99;

		LFAudioSystem::Volume(channel, volume);

		if (LFString::IsEqual(channel, CHSfx))
		{
			if (sfxStream) 
				sfxStream->setVolume(volume / 100.0f);
		}
		else if (LFString::IsEqual(channel, CHMusic))
		{
			if (musicStream) 
				musicStream->setVolume(volume / 100.0f);
		}
	}

	void LFAudioSystemAudiere::Play(const char *channel, const char *soundName)
	{
		LFString soundFullName;
		soundFullName.Append(LFVFSManager::Instance()->Path(LFVFSManager::CP_SOUND));
		soundFullName.Append(soundName);

		musicStreamPosition = 0;

		if (!IsSilentMode())
		{
			if (LFString::IsEqual(channel, CHSfx))
			{
				if (isSFXOn)
				{
					sfxStream = audiere::OpenSound(audioDevice, soundFullName.ToChar(), true);

					if (sfxStream)
					{
						sfxStream->setVolume(volumeSFX / 100.0f);
						sfxStream->setRepeat(false);
						sfxStream->play();
					}
					else
						LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, soundFullName);
				}
			}
			else if(LFString::IsEqual(channel, CHMusic))
			{
				if (isMusicOn)
				{
					musicStream = audiere::OpenSound(audioDevice, soundFullName.ToChar(), true);

					if (musicStream)
					{
						musicStream->setVolume(volumeMusic / 100.0f);
						musicStream->setRepeat(true);
						musicStream->play();
					}
					else
						LFLogger::Instance().WriteOutput(LFLogger::MT_LOAD_ERROR, soundFullName);
				}
			}
		}
	}

	void LFAudioSystemAudiere::Pause()
	{
		if (musicStream) 
		{
			musicStreamPosition = musicStream->getPosition();
			musicStream->stop();
		}
	}

	void LFAudioSystemAudiere::Continue()
	{
		if (isMusicOn && !IsSilentMode() && musicStream && musicStreamPosition > 0)
		{
			musicStream->setVolume(volumeMusic / 100.0f);
			musicStream->setRepeat(true);
			musicStream->setPosition(musicStreamPosition);
			musicStream->play();
		}
	}

	void LFAudioSystemAudiere::Stop(const char *channel)
	{
		musicStreamPosition = 0;

		if (LFString::IsEqual(channel, CHSfx))
		{
			if (sfxStream) 
				sfxStream->stop();
		}
		else if (LFString::IsEqual(channel, CHMusic))
		{
			if (musicStream) 
				musicStream->stop();
		}
	}
}}

#endif
