/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IBaseView.h"

class IOptionsView : public IBaseView
{
public:
	virtual ~IOptionsView() { };

	virtual bool IsMusic() = 0;
	virtual void IsMusic(bool isMusic) = 0;
	virtual unsigned char MusicVolume() = 0;
	virtual void MusicVolume(unsigned char musicVolume) = 0;
	virtual bool IsSfx() = 0;
	virtual void IsSfx(bool isSfx) = 0;
	virtual unsigned char SfxVolume() = 0;
	virtual void SfxVolume(unsigned char sfxVolume) = 0;
};

#endif
