/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "ViewManager.h"

IViewItemsFactory *ViewManager::factory = nullptr;

IViewItemsFactory *ViewManager::Factory()
{
	return factory;
}

void ViewManager::Factory(IViewItemsFactory *factory)
{
	if (ViewManager::factory == nullptr)
		ViewManager::factory = factory;
}

void ViewManager::Release()
{
	delete factory;
}

#endif
