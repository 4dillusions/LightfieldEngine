/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IMainView.h"
#include "IOptionsView.h"
#include "IGameStateView.h"
#include "ILevelView.h"

class IViewItemsFactory
{
public:
	virtual ~IViewItemsFactory() { };

	virtual IMainView *MainViewItem() = 0;
	virtual IOptionsView *OptionsViewItem() = 0;
	virtual IGameStateView *GameStateViewItem() = 0;
	virtual ILevelView *LevelViewItem() = 0;
};

#endif
