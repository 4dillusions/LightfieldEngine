/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#pragma once

#include "..\LFAudioSystem.h"
#include <player.h>

namespace LFEngine { namespace Audio
{
	class LFENGINE_LIBRARY LFAudioSystemTizenPlayer : public LFAudioSystem
	{
	private:
		player_h musicPlayer, sfxPlayer;

	public:
		LFAudioSystemTizenPlayer();
		virtual ~LFAudioSystemTizenPlayer();

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
