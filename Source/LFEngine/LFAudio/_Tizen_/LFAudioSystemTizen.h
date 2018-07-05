/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#pragma once

#include "..\LFAudioSystem.h"
#include <player.h>
#include <telephony.h>

namespace LF3Engine { namespace LFEngine { namespace LFAudio
{
	class LFAudioSystemTizen final : public LFAudioSystem
	{
		player_h musicPlayer, sfxPlayer;
		telephony_handle_list_s handle_list;

		LFAudioSystemTizen(const LFAudioSystemTizen&) = delete;
		LFAudioSystemTizen(LFAudioSystemTizen &&) = delete;
		LFAudioSystemTizen &operator=(const LFAudioSystemTizen &) = delete;
		LFAudioSystemTizen &operator=(LFAudioSystemTizen &&) = delete;

	public:
		LFAudioSystemTizen();
		~LFAudioSystemTizen();
		
		//LFAudioSystem functions
		void SetVolumeSfx(float volume) override;
		void SetVolumeMusic(float volume) override;

		void PlaySfx(const char *soundName) override;
		void PlayMusic(const char *soundName) override;
		void PauseMusic() override;
		void ContinueMusic() override;
		void StopSfx() override;
		void StopMusic() override;
		
		//Tizen functions
		static void PlayerInterrupted(player_interrupted_code_e code, void *user_data);
		static void TelephonySetNoti(telephony_h handle, telephony_noti_e noti_id, void *data, void *user_data);
	};
}}}

#endif
