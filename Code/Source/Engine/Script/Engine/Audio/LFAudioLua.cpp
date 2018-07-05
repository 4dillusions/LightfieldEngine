/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#include "LFAudioLua.h"
#include "..\..\..\Script\LuaHeaders.h"
#include "..\..\..\Script\LFScriptSystem.h"
#include "..\..\..\Audio\LFAudioSystem.h"
#include "..\..\..\..\Core\Common\LFString.h"

using namespace LFEngine::Script;
using namespace LFEngine::Audio;
using namespace LFCore::Common;

int Play(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(3))
	{
		//self //#1
		LFString channel = LFScriptSystem::Instance()->GetStringParameter(2); //#2
		LFString soundName = LFScriptSystem::Instance()->GetStringParameter(3); //#3

		LFAudioSystem::Instance()->Play(channel.ToChar(), soundName.ToChar());
	}

	return 0; //no return values
}

int Stop(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		LFString channel = LFScriptSystem::Instance()->GetStringParameter(2); //#2

		LFAudioSystem::Instance()->Stop(channel.ToChar());
	}

	return 0; //no return values
}

int GetVolume(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		LFString channel = LFScriptSystem::Instance()->GetStringParameter(2); //#2

		LFScriptSystem::Instance()->PushNumber(LFAudioSystem::Instance()->Volume(channel.ToChar()));
	}

	return 1; //return volume
}

int SetVolume(lua_State *luaState)
{
	if(LFScriptSystem::Instance()->IsParamCountOk(3))
	{
		//self //#1
		LFString channel = LFScriptSystem::Instance()->GetStringParameter(2); //#2
		int volume = LFScriptSystem::Instance()->GetNumberParameter(3); //#3

		LFAudioSystem::Instance()->Volume(channel.ToChar(), volume);
	}

	return 0; //no return values
}

int GetVolumeOn(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(2))
	{
		//self //#1
		LFString channel = LFScriptSystem::Instance()->GetStringParameter(2); //#2

		LFScriptSystem::Instance()->PushBoolean(LFAudioSystem::Instance()->VolumeOn(channel.ToChar()));
	}

	return 1; //return volume on
}

int SetVolumeOn(lua_State *luaState)
{
	if (LFScriptSystem::Instance()->IsParamCountOk(3))
	{
		//self //#1
		LFString channel = LFScriptSystem::Instance()->GetStringParameter(2); //#2
		bool isOn = LFScriptSystem::Instance()->GetBooleanParameter(3); //#3

		LFAudioSystem::Instance()->VolumeOn(channel.ToChar(), isOn);
	}

	return 0; //no return values
}

/**
@defgroup Audio

@defgroup LFAudio
@ingroup Audio

@page my_AudioPlay Play
@ingroup LFAudio
Play music or sfx sounds. <br>
[Lua API]<br>
@code
LFAudio:Play(string channel, string soundName)
@endcode
@param[in] channel <br>
sfx "CH_SFX", music "CH_MUSIC"<br>
@param[in] soundName <br>
"mySfx.wav", "myMusic.mp3"

@page my_AudioStop Stop
@ingroup LFAudio
Stop music or sfx sounds. <br>
[Lua API]<br>
@code
LFAudio:Stop(string channel)
@endcode
@param[in] channel <br>
sfx "CH_SFX", music "CH_MUSIC"<br>

@page my_AudioGetVolume GetVolume
@ingroup LFAudio
Get music or sfx volume. <br>
[Lua API]<br>
@code
number LFAudio:GetVolume(string channel)
@endcode
@param[in] channel <br>
sfx "CH_SFX", music "CH_MUSIC"

@page my_AudioSetVolume SetVolume
@ingroup LFAudio
Set music or sfx volume. <br>
[Lua API]<br>
@code
LFAudio:SetVolume(string channel, number volume)
@endcode
@param[in] channel <br>
sfx "CH_SFX", music "CH_MUSIC"
@param[in] volume <br>
Set volume 1 to 100

@page my_AudioGetVolumeOn GetVolumeOn
@ingroup LFAudio
Get music or sfx volume on. <br>
[Lua API]<br>
@code
bool LFAudio:GetVolumeOn(string channel)
@endcode
@param[in] channel <br>
sfx "CH_SFX", music "CH_MUSIC"

@page my_AudioSetVolumeOn SetVolumeOn
@ingroup LFAudio
Set music or sfx volume on. <br>
[Lua API]<br>
@code
LFAudio:SetVolumeOn(string channel, bool isOn)
@endcode
@param[in] channel <br>
sfx "CH_SFX", music "CH_MUSIC"
@param[in] isOn <br>
mute or nope
*/
luaL_Reg LFAudioFunctions[] =
{
	//{ "New", Constructor }, 
	//{ "__gc", Destructor }, 
	{ "Play", Play },
	{ "Stop", Stop },
	{ "GetVolume", GetVolume },
	{ "SetVolume", SetVolume },
	{ "GetVolumeOn", GetVolumeOn },
	{ "SetVolumeOn", SetVolumeOn },
	{ 0, 0 }
};

luaL_Reg *GetLFAudioFunctions()
{
	return LFAudioFunctions;
}
