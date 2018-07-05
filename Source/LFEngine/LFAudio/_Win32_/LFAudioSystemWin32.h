/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WINCLASSIC

#pragma once

#include "..\LFAudioSystem.h"
#include "..\..\..\ThirdParty\_Win32_\Audiere\audiere.h"

namespace LF3Engine { namespace LFEngine { namespace LFAudio
{
	class LFAudioSystemWin32 final : public LFAudioSystem
	{
		audiere::AudioDevicePtr audioDevice;
		audiere::OutputStreamPtr sfxStream, musicStream;
		int musicStreamPosition;

		LFAudioSystemWin32(const LFAudioSystemWin32&) = delete;
		LFAudioSystemWin32(LFAudioSystemWin32 &&) = delete;
		LFAudioSystemWin32 &operator=(const LFAudioSystemWin32 &) = delete;
		LFAudioSystemWin32 &operator=(LFAudioSystemWin32 &&) = delete;

	public:
		LFAudioSystemWin32();
		~LFAudioSystemWin32() = default;

		//LFAudioSystem functions
		void SetVolumeSfx(float volume) override;
		void SetVolumeMusic(float volume) override;

		void PlaySfx(const char *soundName) override;
		void PlayMusic(const char *soundName) override;
		void PauseMusic() override;
		void ContinueMusic() override;
		void StopSfx() override;
		void StopMusic() override;
	};
}}}

#endif
