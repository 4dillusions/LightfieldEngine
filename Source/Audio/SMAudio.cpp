#include "SMAudio.h"
#include "..\\Core\\SMCore.h"
#include "..\\Core\\SMContentManager.h"
#include "..\\Engine\\SMSystemInfo.h"

using namespace SMEngine::Engine;

namespace SMEngine { namespace Audio
{
	SMAudio *SMAudio::instance = 0;

	SMAudio::SMAudio() : isMusicLoaded(false), isSfxLoaded(false), isMusicOn(true), isSFXon(true), volumeMusic(99), volumeSFX(99)
	{
		musicPlayer = new Player();
		musicPlayer->Construct(*this, 0);
		musicPlayer->SetLooping(true);

		sfxPlayer = new Player();
		sfxPlayer->Construct(*this, 0);
	}

	SMAudio::~SMAudio()
	{
		if(musicPlayer != nullptr)
		{
			PlayerState nowState = musicPlayer->GetState();
			if(nowState == PLAYER_STATE_PLAYING || nowState == PLAYER_STATE_PAUSED )
			{
				musicPlayer->Stop();
				musicPlayer->Close();
			}else if(nowState == PLAYER_STATE_OPENED || nowState == PLAYER_STATE_ENDOFCLIP || nowState == PLAYER_STATE_STOPPED )
			{
				musicPlayer->Close();
			}

			delete musicPlayer;
			musicPlayer = nullptr;
		}

		if(sfxPlayer != nullptr)
		{
			PlayerState nowState = sfxPlayer->GetState();
			if(nowState == PLAYER_STATE_PLAYING || nowState == PLAYER_STATE_PAUSED )
			{
				sfxPlayer->Stop();
				sfxPlayer->Close();
			}else if(nowState == PLAYER_STATE_OPENED || nowState == PLAYER_STATE_ENDOFCLIP || nowState == PLAYER_STATE_STOPPED )
			{
				sfxPlayer->Close();
			}

			delete sfxPlayer;
			sfxPlayer = nullptr;
		}
	}

	SMAudio *SMAudio::Instance()
	{
		return instance;
	}

	void SMAudio::CreateInstance()
	{
		if (instance == nullptr)
			instance = new SMAudio();
	}

	void SMAudio::ReleaseInstance()
	{
		if (instance != nullptr)
			delete instance;
	}

	void SMAudio::PlaySound(const Channel &channel, const char *soundName)
	{
		SMString soundFullName;
		soundFullName.Append(SMContentManager::Instance().Path(SMContentManager::CP_SOUND));
		soundFullName.Append(soundName);

		StopSound(channel);
		SetSoundOn(channel, true);

		switch(channel)
		{
			case MUSIC:
				if (!isMusicLoaded)
					isMusicLoaded = true;
				else
					musicPlayer->Close();

				if (isMusicOn)
				{
					musicPlayer->OpenFile(soundFullName.ToBadaString());
					musicPlayer->SetVolume(0);
					musicPlayer->Play();
					if (SMSystemInfo::Instance().IsSilentMode()) PauseSound(channel);
					SetSoundVolume(channel, volumeMusic);
				}
				break;

			case SFX:
				if (!isSfxLoaded)
					isSfxLoaded = true;
				else
					sfxPlayer->Close();

				if (isSFXon)
				{
					sfxPlayer->OpenFile(soundFullName.ToBadaString());
					sfxPlayer->SetVolume(0);
					sfxPlayer->Play();
					if (SMSystemInfo::Instance().IsSilentMode()) PauseSound(channel);
					SetSoundVolume(channel, volumeSFX);
				}
				break;
		}
	}

	//pause utáni lejátszás
	void SMAudio::PlaySound(const Channel &channel)
	{
		if (!SMSystemInfo::Instance().IsSilentMode())
		{
			switch(channel)
			{
				case MUSIC:
					if (isMusicOn && musicPlayer->GetState() == PLAYER_STATE_PAUSED)
					{
						musicPlayer->Play();
						SetSoundVolume(channel, volumeMusic);
					}
					break;

				case SFX:
					if (isSFXon && sfxPlayer->GetState() == PLAYER_STATE_PAUSED)
					{
						sfxPlayer->Play();
						SetSoundVolume(channel, volumeSFX);
					}
					break;
			}
		}
	}

	//pause utáni lejátszás
	void SMAudio::PlayAllSound()
	{
		PlaySound(MUSIC);
		PlaySound(SFX);
	}

	void SMAudio::StopSound(const Channel &channel)
	{
		SetSoundOn(channel, false);

		switch(channel)
		{
			case MUSIC:
				if (musicPlayer->GetState() == PLAYER_STATE_PLAYING)
					musicPlayer->Stop();
				break;

			case SFX:
				if (sfxPlayer->GetState() == PLAYER_STATE_PLAYING)
					sfxPlayer->Stop();
				break;
		}
	}

	void SMAudio::StopAllSound()
	{
		StopSound(MUSIC);
		StopSound(SFX);
	}

	void SMAudio::PauseSound(const Channel &channel)
	{
		switch(channel)
		{
			case MUSIC:
				if (musicPlayer->GetState() == PLAYER_STATE_PLAYING)
					musicPlayer->Pause();
				break;

			case SFX:
				if (sfxPlayer->GetState() == PLAYER_STATE_PLAYING)
					sfxPlayer->Pause();
				break;
		}
	}

	void SMAudio::PauseAllSound()
	{
		PauseSound(MUSIC);
		PauseSound(SFX);
	}

	void SMAudio::SetSoundVolume(const Channel &channel, int volume)
	{
		//0-99 az API-ban, nálam 1-100 ig
		if (volume < 0)
			volume = 0;

		if (volume > 99)
			volume = 99;

		switch(channel)
		{
			case MUSIC:
				volumeMusic = volume;

				if (musicPlayer->GetState() == PLAYER_STATE_PLAYING)
					musicPlayer->SetVolume(volume);
				break;

			case SFX:
				volumeSFX = volume;

				if (sfxPlayer->GetState() == PLAYER_STATE_PLAYING)
					sfxPlayer->SetVolume(volume);
				break;
		}
	}

	int SMAudio::GetSoundVolume(const Channel &channel)
	{
		switch(channel)
		{
			case MUSIC: return volumeMusic;
			case SFX: return volumeSFX;
		}

		return 0;
	}

	void SMAudio::SetSoundOn(const Channel &channel, bool on)
	{
		switch(channel)
		{
			case MUSIC: isMusicOn = on;
			case SFX: isSFXon = on;
		}
	}

	bool SMAudio::GetSoundOn(const Channel &channel)
	{
		switch(channel)
		{
			case MUSIC: return isMusicOn;
			case SFX: return isSFXon;
		}

		return false;
	}

	void SMAudio::OnPlayerOpened(result r)
	{ }

	void SMAudio::OnPlayerEndOfClip()
	{ }

	void SMAudio::OnPlayerBuffering(int percent)
	{ }

	void SMAudio::OnPlayerErrorOccurred(PlayerErrorReason r)
	{ }

	void SMAudio::OnPlayerInterrupted()
	{ }

	void SMAudio::OnPlayerReleased()
	{ }
};};
