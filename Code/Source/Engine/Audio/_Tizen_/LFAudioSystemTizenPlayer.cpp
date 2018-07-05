/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef TIZEN

#include "LFAudioSystemTizenPlayer.h"
#include "..\..\..\..\LFCore\src\Common\LFMemoryManager.h"
#include "..\..\..\..\LFCore\src\Common\LFString.h"
#include "..\..\..\..\LFCore\src\Common\LFVFSManager.h"
#include "..\..\..\..\LFCore\src\IO\LFLogger.h"

#include <app.h>
#include <telephony.h>

telephony_handle_list_s handle_list;

using namespace LFCore::Common;
using namespace LFCore::IO;

void player_interrupted(player_interrupted_code_e code, void *user_data)
{
	if (code == PLAYER_INTERRUPTED_COMPLETED)
	{
		LFLogger::Instance().WriteOutput(LFLogger::MT_WARNING, "Media player interrupt completed! (music stream)");
		LFEngine::Audio::LFAudioSystem::Instance()->Continue();
	}
	else
	{
		LFLogger::Instance().WriteOutput(LFLogger::MT_WARNING, "Media player interrupted! (music stream)");
	}
}

void telephony_set_noti(telephony_h handle, telephony_noti_e noti_id, void *data, void *user_data)
{
	telephony_call_state_e state = *(telephony_call_state_e *)data; //hivas: connecting, lerakas: idle
	if (state == TELEPHONY_CALL_STATE_CONNECTING)
	{
		LFLogger::Instance().WriteOutput(LFLogger::MT_WARNING, "Telephony call start. Music interrupted!");
	}
	else if (state == TELEPHONY_CALL_STATE_IDLE)
	{
		LFLogger::Instance().WriteOutput(LFLogger::MT_WARNING, "Telephony call end. Music continue!");
		LFEngine::Audio::LFAudioSystem::Instance()->Continue();
	}
}

namespace LFEngine { namespace Audio
{
	LFAudioSystemTizenPlayer::LFAudioSystemTizenPlayer()
	{
		int errorCode = 0;

		errorCode = player_create(&sfxPlayer);
		if (errorCode != PLAYER_ERROR_NONE)
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player construct failed! (sfx stream)");

		errorCode = player_create(&musicPlayer);
		if (errorCode != PLAYER_ERROR_NONE)
			LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player construct failed! (music stream)");
		else
		{
			player_set_interrupted_cb(musicPlayer, player_interrupted, nullptr);

			telephony_init(&handle_list);
			telephony_set_noti_cb(handle_list.handle[0], TELEPHONY_NOTI_VOICE_CALL_STATE, telephony_set_noti, nullptr);
		}
	}

	LFAudioSystemTizenPlayer::~LFAudioSystemTizenPlayer()
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

	void LFAudioSystemTizenPlayer::CreateInstance()
	{
		if (instance == nullptr)
			instance = LFNew<LFAudioSystemTizenPlayer>(AT);
	}

	void LFAudioSystemTizenPlayer::ReleaseInstance()
	{
		if (instance != nullptr)
			LFDelete(instance);
	}

	void LFAudioSystemTizenPlayer::Volume(const char *channel, int volume)
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		if (volume < 1)
			volume = 1;

		if (volume > 100)
			volume = 100;

		LFAudioSystem::Volume(channel, volume);

		//convert to Tizen player volume
		float tizenVolume = volume / 100.0f;

		if (LFString::IsEqual(channel, CHSfx))
		{
			player_get_state(sfxPlayer, &state);
			if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
			{
				errorCode = player_set_volume(sfxPlayer, tizenVolume, tizenVolume);

				if (errorCode != PLAYER_ERROR_NONE)
					LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player set volume failed! (sfx stream)");
			}
		}
		else if(LFString::IsEqual(channel, CHMusic))
		{
			player_get_state(musicPlayer, &state);
			if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
			{
				errorCode = player_set_volume(musicPlayer, tizenVolume, tizenVolume);

				if (errorCode != PLAYER_ERROR_NONE)
					LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player set volume failed! (music stream)");
			}
		}
	}

	void LFAudioSystemTizenPlayer::Play(const char *channel, const char *soundName)
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		LFString soundFullName;
		soundFullName.Append(LFVFSManager::Instance()->Path(LFVFSManager::CP_SOUND));
		soundFullName.Append(soundName);

		float tizenSfxVolume = volumeSFX / 10.0f;
		float tizenMusicVolume = volumeMusic / 10.0f;

		if (!IsSilentMode())
		{
			if (LFString::IsEqual(channel, CHSfx))
			{
				if (isSFXOn)
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
					errorCode = player_set_volume(sfxPlayer, tizenSfxVolume, tizenSfxVolume);
					errorCode = player_prepare(sfxPlayer);
					errorCode = player_start(sfxPlayer);

					if (errorCode != PLAYER_ERROR_NONE)
						LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player Play failed! (sfx stream)");
				}
			}
			else if(LFString::IsEqual(channel, CHMusic))
			{
				if (isMusicOn)
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
					errorCode = player_set_volume(musicPlayer, tizenMusicVolume, tizenMusicVolume);
					errorCode = player_prepare(musicPlayer);
					errorCode = player_start(musicPlayer);

					if (errorCode != PLAYER_ERROR_NONE)
						LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player Play failed! (music stream)");
				}
			}
		}
	}

	void LFAudioSystemTizenPlayer::Pause()
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		player_get_state(sfxPlayer, &state);
		if(state == PLAYER_STATE_PLAYING)
		{
			errorCode = player_stop(sfxPlayer);
			if (errorCode != PLAYER_ERROR_NONE)
				LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player Pause failed! (sfx stream)");
		}

		player_get_state(musicPlayer, &state);
		if(state == PLAYER_STATE_PLAYING)
		{
			errorCode = player_pause(musicPlayer);
			if (errorCode != PLAYER_ERROR_NONE)
				LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player Pause failed! (music stream)");
		}
	}

	void LFAudioSystemTizenPlayer::Continue()
	{
		int errorCode = 0;
		float tizenMusicVolume = volumeMusic / 10.0f;

		if (isMusicOn && !IsSilentMode())
		{
			player_state_e state = PLAYER_STATE_NONE;
			player_get_state(musicPlayer, &state);

			if(state == PLAYER_STATE_PAUSED)
			{
				errorCode = player_set_looping(musicPlayer, true);
				errorCode = player_set_volume(musicPlayer, tizenMusicVolume, tizenMusicVolume);
				errorCode = player_start(musicPlayer);

				if (errorCode != PLAYER_ERROR_NONE)
					LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player Continue failed! (music stream)");
			}
		}
	}

	void LFAudioSystemTizenPlayer::Stop(const char *channel)
	{
		player_state_e state = PLAYER_STATE_NONE;
		int errorCode = 0;

		if (LFString::IsEqual(channel, CHSfx))
		{
			player_get_state(sfxPlayer, &state);
			if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
			{
				errorCode = player_stop(sfxPlayer);
				if (errorCode != PLAYER_ERROR_NONE)
					LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player Stop failed! (sfx stream)");
			}
		}
		else if(LFString::IsEqual(channel, CHMusic))
		{
			player_get_state(musicPlayer, &state);
			if(state == PLAYER_STATE_PLAYING || state == PLAYER_STATE_PAUSED)
			{
				errorCode = player_stop(musicPlayer);
				if (errorCode != PLAYER_ERROR_NONE)
					LFLogger::Instance().WriteOutput(LFLogger::MT_ERROR, "Media player Stop failed! (music stream)");
			}
		}
	}
}}

#endif
