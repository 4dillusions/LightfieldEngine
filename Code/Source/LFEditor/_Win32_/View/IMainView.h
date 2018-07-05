/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include <iostream>
#include <functional>
#include "MenuItems.h"

class IMainView
{
public:
	virtual ~IMainView() { };
	std::function<void(MenuItems menuItem)> MenuButtonCommand = nullptr;

	virtual void ShowWindow() = 0;
};

#endif