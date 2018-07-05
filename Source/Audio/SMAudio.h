#pragma once

#include "..\\Core\\SMString.h"
#include "FMediaPlayer.h"

using namespace SMEngine::Core;
using namespace Osp::Media;

namespace SMEngine { namespace Audio
{
	/*
	Hanglej�tsz�s: 2 csatorn�s Zene/Sfx
	Az SMAudio instance-t AppInitializing-ban kell inicializ�lni. K�zzel kell felszabad�tani is!

	Haszn�lat:
	bool SMWindow::OnAppInitializing(AppRegistry &appRegistry)
	{
		SMAudio::CreateInstance();

		return true;
	}
	...
	SMAudio::Instance()->PlaySound(SMAudio::MUSIC, "tetris.mp3");
	SMAudio::Instance()->SetSoundVolume(SMAudio::MUSIC, 50);
	...
	SMAudio::Instance()->PlaySound(SMAudio::MUSIC); //bet�lt�tt zen�n�l pause ut�n
	*/
	class SMAudio : public IPlayerEventListener
	{
	private:
		SMAudio();
		virtual ~SMAudio();

		static SMAudio *instance;
		Player *musicPlayer, *sfxPlayer;
		bool isMusicLoaded, isSfxLoaded; //az els� bet�lt�s el�tt nem lehet close, ez�rt kell figyelni.
		bool isMusicOn, isSFXon; //be van e kapcsolva a lej�tsz�s
		int volumeMusic, volumeSFX;

	public:
		enum Channel { MUSIC, SFX };

		static SMAudio *Instance();
		static void CreateInstance();
		static void ReleaseInstance();

		void PlaySound(const Channel &channel, const char *soundName);
		void PlaySound(const Channel &channel);
		void PlayAllSound();
		void StopSound(const Channel &channel);
		void StopAllSound();
		void PauseSound(const Channel &channel);
		void PauseAllSound();
		void SetSoundVolume(const Channel &channel, int volume);
		int GetSoundVolume(const Channel &channel);
		void SetSoundOn(const Channel &channel, bool on);
		bool GetSoundOn(const Channel &channel);

		virtual void OnPlayerOpened(result r);
		virtual void OnPlayerEndOfClip();
		virtual void OnPlayerBuffering(int percent);
		virtual void OnPlayerErrorOccurred(PlayerErrorReason r);
		virtual void OnPlayerInterrupted();
		virtual void OnPlayerReleased();
	};
};};
