/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IBaseView.h"

class IGameStateView : public IBaseView
{
public:
	virtual ~IGameStateView() { };

	std::function<void()> LevelButtonCommand = nullptr;

	virtual unsigned char LevelIndex() = 0;
	virtual void LevelIndex(unsigned char levelIndex) = 0;
	virtual unsigned short Second() = 0;
	virtual void Second(unsigned short second) = 0;
	virtual unsigned short Lives() = 0;
	virtual void Lives(unsigned short lives) = 0;
};

#endif
