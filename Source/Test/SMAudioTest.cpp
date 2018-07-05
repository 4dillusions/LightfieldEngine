#include "SMAudioTest.h"
#include "..\\Test\\SMTest.h"
#include "..\\Audio\\SMAudio.h"

using namespace SMEngine::Audio;

namespace SMEngine { namespace Test
{
    void SMAudioTest::SMPlayMusicTest()
    {
    	SMAudio::Instance()->PlaySound(SMAudio::MUSIC, "blackOrWhite.mp3");
    	SMAudio::Instance()->SetSoundVolume(SMAudio::MUSIC, 10);
    }
};};
