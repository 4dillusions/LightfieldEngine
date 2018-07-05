/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\View\IMainView.h"

class MainViewController
{
public:
	MainViewController(IMainView *view);
	~MainViewController();

	void MenuButtonCommand(MenuItems menuItem);

private:
	IMainView *view;
};

#endif
