/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#pragma once

#include "..\LFEngine.h"

namespace LFEngine { namespace Audio
{
	#define CHSfx "CH_SFX"
	#define CHMusic "CH_MUSIC"

	class LFENGINE_LIBRARY LFAudioSystem
	{ 
	protected:
		static LFAudioSystem *instance;
		
		bool isMusicOn, isSFXOn;
		int volumeMusic, volumeSFX;

	public:
		LFAudioSystem();
		virtual ~LFAudioSystem();

		static LFAudioSystem *Instance() { return instance; }

		bool IsSilentMode();
		void VolumeOn(const char *channel, bool isOn);
		bool VolumeOn(const char *channel);
		virtual void Volume(const char *channel, int volume);
		int Volume(const char *channel);

		virtual void Play(const char *channel, const char *soundName) = 0;
		virtual void Pause() = 0;
		virtual void Continue() = 0;
		virtual void Stop(const char *channel) = 0;
	};
}}
