/*
Copyright (c) 2011-2017 by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#include "LFAudioSystemTizen.h"
#include "..\..\LFCore\LFPatterns\LFIoc.h"
#include "..\..\LFCore\LFIO\LFLogger.h"
#include "..\..\LFCore\LFCommon\LFVFSManager.h"

using namespace LF3Engine::LFEngine::LFCore::LFPatterns;
using namespace LF3Engine::LFEngine::LFCore::LFIO;
using namespace LF3Engine::LFEngine::LFCore::LFCommon;

namespace LF3Engine { namespace LFEngine { namespace LFAudio
{
	LFAudioSystemTizen::LFAudioSystemTizen() : musicPlayer(nullptr), sfxPlayer(nullptr)
	{
		audio = this;

		int errorCode = 0;

		errorCode = player_create(&sfxPlayer);
		if (errorCode != PLAYER_ERROR_NONE)
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player construct failed! (sfx stream)");

		errorCode = player_create(&musicPlayer);
		if (errorCode != PLAYER_ERROR_NONE)
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player construct failed! (music stream)");
		else
		{
			player_set_interrupted_cb(musicPlayer, PlayerInterrupted, nullptr);

			int ret = telephony_init(&handle_list);
			if (ret != TELEPHONY_ERROR_NONE)
			{
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Telephony error!");
				return;
			}

			telephony_set_noti_cb(handle_list.handle[0], TELEPHONY_NOTI_VOICE_CALL_STATE, TelephonySetNoti, nullptr);
		}
	}
	
	LFAudioSystemTizen::~LFAudioSystemTizen()
	{ 
		player_stop(sfxPlayer);
		player_unprepare(sfxPlayer);
		player_destroy(sfxPlayer);
		sfxPlayer = 0;

		player_stop(musicPlayer);
		player_unprepare(musicPlayer);
		player_destroy(musicPlayer);
		musicPlayer = 0;
	}
	
	void LFAudioSystemTizen::SetVolumeSfx(float volume)
	{
		LFAudioSystem::SetVolumeSfx(volume);

		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		player_get_state(sfxPlayer, &state);
		if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
		{
			errorCode = player_set_volume(sfxPlayer, volumeSFX, volumeSFX);

			if (errorCode != PLAYER_ERROR_NONE)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player set volume failed! (sfx stream)");
		}
	}

	void LFAudioSystemTizen::SetVolumeMusic(float volume)
	{
		LFAudioSystem::SetVolumeMusic(volume);

		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		player_get_state(musicPlayer, &state);
		if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
		{
			errorCode = player_set_volume(musicPlayer, volumeMusic, volumeMusic);

			if (errorCode != PLAYER_ERROR_NONE)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player set volume failed! (music stream)");
		}
	}

	void LFAudioSystemTizen::PlaySfx(const char *soundName)
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		LFString soundFullName(vfsManager->GetPath(LFVFSPath::Sound));
		soundFullName += soundName;

		if (!IsSilentMode() && isSFXOn)
		{
			player_get_state(sfxPlayer, &state);
			if(state == PLAYER_STATE_PLAYING)
			{
				player_stop(sfxPlayer);
				player_unprepare(sfxPlayer);
			}

			errorCode = player_set_uri(sfxPlayer, soundFullName.ToChar());
			errorCode = player_set_sound_type(sfxPlayer, SOUND_TYPE_MEDIA);
			errorCode = player_set_looping(sfxPlayer, false);
			errorCode = player_set_volume(sfxPlayer, volumeSFX, volumeSFX);
			errorCode = player_prepare(sfxPlayer);
			errorCode = player_start(sfxPlayer);

			if (errorCode != PLAYER_ERROR_NONE)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player Play failed! (sfx stream)");
		}
	}

	void LFAudioSystemTizen::PlayMusic(const char *soundName)
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		LFString soundFullName(vfsManager->GetPath(LFVFSPath::Sound));
		soundFullName += soundName;

		if (!IsSilentMode() && isMusicOn)
		{
			player_get_state(musicPlayer, &state);
			if(state == PLAYER_STATE_PLAYING)
			{
				player_stop(musicPlayer);
				player_unprepare(musicPlayer);
			}

			errorCode = player_set_uri(musicPlayer, soundFullName.ToChar());
			errorCode = player_set_sound_type(musicPlayer, SOUND_TYPE_MEDIA);
			errorCode = player_set_looping(musicPlayer, true);
			errorCode = player_set_volume(musicPlayer, volumeMusic, volumeMusic);
			errorCode = player_prepare(musicPlayer);
			errorCode = player_start(musicPlayer);

			if (errorCode != PLAYER_ERROR_NONE)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player Play failed! (music stream)");
		}
	}

	void LFAudioSystemTizen::PauseMusic()
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		player_get_state(musicPlayer, &state);
		if(state == PLAYER_STATE_PLAYING)
		{
			errorCode = player_pause(musicPlayer);
			if (errorCode != PLAYER_ERROR_NONE)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player Pause failed! (music stream)");
		}
	}

	void LFAudioSystemTizen::ContinueMusic()
	{
		int errorCode = 0;

		if (isMusicOn && !IsSilentMode())
		{
			player_state_e state = PLAYER_STATE_NONE;
			player_get_state(musicPlayer, &state);

			if(state == PLAYER_STATE_PAUSED)
			{
				errorCode = player_set_looping(musicPlayer, true);
				errorCode = player_set_volume(musicPlayer, volumeMusic, volumeMusic);
				errorCode = player_start(musicPlayer);

				if (errorCode != PLAYER_ERROR_NONE)
					LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player Continue failed! (music stream)");
			}
		}
	}

	void LFAudioSystemTizen::StopSfx()
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		player_get_state(sfxPlayer, &state);
		if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
		{
			errorCode = player_stop(sfxPlayer);
			if (errorCode != PLAYER_ERROR_NONE)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player Stop failed! (sfx stream)");
		}
	}

	void LFAudioSystemTizen::StopMusic()
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		player_get_state(musicPlayer, &state);
		if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
		{
			errorCode = player_stop(musicPlayer);
			if (errorCode != PLAYER_ERROR_NONE)
				LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Error, "Media player Stop failed! (music stream)");
		}
	}
	
	void LFAudioSystemTizen::PlayerInterrupted(player_interrupted_code_e code, void *user_data)
	{
		if (code == PLAYER_INTERRUPTED_COMPLETED)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Warning, "Media player interrupt completed! (music stream)");
			audio->ContinueMusic();
		}
		else
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Warning, "Media player interrupted! (music stream)");
		}
	}
	
	void LFAudioSystemTizen::TelephonySetNoti(telephony_h handle, telephony_noti_e noti_id, void *data, void *user_data)
	{
		telephony_call_state_e state = *(telephony_call_state_e *)data; //call: connecting, end call: idle
		if (state == TELEPHONY_CALL_STATE_CONNECTING)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Warning, "Telephony call start. Music interrupted!");
		}
		else if (state == TELEPHONY_CALL_STATE_IDLE)
		{
			LFIoc<LFLogger>::Get().WriteOutput(LFLogMessageType::Warning, "Telephony call end. Music continue!");
			audio->ContinueMusic();
		}
	}
}}}

#endif
