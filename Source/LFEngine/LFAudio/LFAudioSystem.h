/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

namespace LF3Engine { namespace LFEngine { namespace LFCore { namespace LFCommon
{
	class LFVFSManager;
}}}}

namespace LF3Engine { namespace LFEngine { namespace LFAudio
{
	/** 
		@brief 
		Audio subsystem for PC and mobile devices
	*/
	class LFAudioSystem
	{
		LFAudioSystem(const LFAudioSystem&) = delete;
		LFAudioSystem(LFAudioSystem &&) = delete;
		LFAudioSystem &operator=(const LFAudioSystem &) = delete;
		LFAudioSystem &operator=(LFAudioSystem &&) = delete;

	protected:
		bool isMusicOn, isSFXOn;
		float volumeMusic, volumeSFX;
		LFCore::LFCommon::LFVFSManager *vfsManager;

		static LFAudioSystem *audio;

	public:
		LFAudioSystem();
		virtual ~LFAudioSystem();

		static bool IsSilentMode();
		void SetIsVolumeOnSfx(bool isOn);
		void SetIsVolumeOnMusic(bool isOn);
		bool GetIsVolumeOnSfx() const;
		bool GetIsVolumeOnMusic() const;
		float GetVolumeSfx() const;
		float GetVolumeMusic() const;

		virtual void SetVolumeSfx(float volume);
		virtual void SetVolumeMusic(float volume);

		virtual void PlaySfx(const char *soundName) = 0;
		virtual void PlayMusic(const char *soundName) = 0;
		virtual void PauseMusic() = 0;
		virtual void ContinueMusic() = 0;
		virtual void StopSfx() = 0;
		virtual void StopMusic() = 0;
	};
}}}
