/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "ViewItemsFactory.h"
#include "OptionsView.h"
#include "GameStateView.h"
#include "LevelView.h"

ViewItemsFactory::ViewItemsFactory(IMainView *mainViewItem) : mainViewItem(mainViewItem)
{ }

ViewItemsFactory::~ViewItemsFactory()
{
	if (optionsViewItem != nullptr)
		delete optionsViewItem;

	if (gameStateViewItem != nullptr)
		delete gameStateViewItem;

	if (levelViewItem != nullptr)
		delete levelViewItem;
}

IMainView *ViewItemsFactory::MainViewItem()
{
	return mainViewItem;
}

IOptionsView *ViewItemsFactory::OptionsViewItem()
{
	if (optionsViewItem == nullptr)
		optionsViewItem = new OptionsView();

	return optionsViewItem;
}

IGameStateView *ViewItemsFactory::GameStateViewItem()
{
	if (gameStateViewItem == nullptr)
		gameStateViewItem = new GameStateView();

	return gameStateViewItem;
}

ILevelView *ViewItemsFactory::LevelViewItem()
{
	if (levelViewItem == nullptr)
		levelViewItem = new LevelView();

	return levelViewItem;
}

#endif
