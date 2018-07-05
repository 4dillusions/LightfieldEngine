/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\View\IViewItemsFactory.h"

class ViewManager
{
public:
	static IViewItemsFactory *Factory();
	static void Factory(IViewItemsFactory *factory);
	static void Release();

private:
	static IViewItemsFactory *factory;
};

#endif
