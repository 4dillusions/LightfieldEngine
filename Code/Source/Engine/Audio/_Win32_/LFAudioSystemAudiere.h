/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\LFAudioSystem.h"
#include "..\..\..\..\Source\Depencies\Audiere\include\audiere.h"

namespace LFEngine { namespace Audio
{
	template class LFENGINE_LIBRARY audiere::RefPtr<audiere::AudioDevice>;
	template class LFENGINE_LIBRARY audiere::RefPtr<audiere::OutputStream>;

	class LFENGINE_LIBRARY LFAudioSystemAudiere : public LFAudioSystem
	{ 
	private:
		audiere::AudioDevicePtr audioDevice;
		audiere::OutputStreamPtr musicStream, sfxStream;
		int musicStreamPosition;

	public:
		LFAudioSystemAudiere();
		virtual ~LFAudioSystemAudiere() { }

		static void CreateInstance();
		static void ReleaseInstance();

		virtual void Volume(const char *channel, int volume);

		virtual void Play(const char *channel, const char *soundName);
		virtual void Pause();
		virtual void Continue();
		virtual void Stop(const char *channel);
	};
}}

#endif