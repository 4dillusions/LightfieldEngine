/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IViewItemsFactory.h"

class ViewItemsFactory : public IViewItemsFactory
{
public:
	IMainView *MainViewItem() override;
	IOptionsView *OptionsViewItem() override;
	IGameStateView *GameStateViewItem() override;
	ILevelView *LevelViewItem() override;

	ViewItemsFactory(IMainView *mainViewItem);
	~ViewItemsFactory() override;

private:
	IMainView *mainViewItem = nullptr;
	IOptionsView *optionsViewItem = nullptr;
	IGameStateView *gameStateViewItem = nullptr;
	ILevelView *levelViewItem = nullptr;
};

#endif
