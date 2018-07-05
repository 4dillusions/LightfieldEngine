/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "MainViewController.h"
#include "ViewManager.h"
#include "..\View\ViewItemsFactory.h"

MainViewController::MainViewController(IMainView *view) : view(view)
{
	ViewManager::Factory(new ViewItemsFactory(view));

	view->MenuButtonCommand = std::bind(&MainViewController::MenuButtonCommand, this, std::placeholders::_1);
}

MainViewController::~MainViewController()
{
	ViewManager::Release();
}

void MainViewController::MenuButtonCommand(MenuItems menuItem)
{
	switch (menuItem)
	{
	case MenuItems::Options: ViewManager::Factory()->OptionsViewItem()->ShowWindow(); break;
	case MenuItems::GameState: ViewManager::Factory()->GameStateViewItem()->ShowWindow(); break;
	case MenuItems::Level: ViewManager::Factory()->LevelViewItem()->ShowWindow(); break;
	}
}

#endif
