/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "ToolbarItems.h"
#include <iostream>
#include <functional>
#include <QCloseEvent>

class BaseViewController;

class IBaseView
{
public:
	virtual ~IBaseView() { };

	std::function<void()> ShowCommand = nullptr;
	std::function<void(QCloseEvent *event)> CloseCommand = nullptr;
	std::function<void(ToolbarItems toolBarItem)> ToolButtonCommand = nullptr;
	std::function<void()> ControlStateChangedCommand = nullptr;

	virtual void ShowWindow() = 0;
	virtual void HideWindow() = 0;
	virtual bool IsModified() = 0;
	virtual void IsModified(bool isModified) = 0;
	virtual void Title(const QString &title) = 0;
	virtual QString Title() = 0;
	virtual bool IsDetailWindow() = 0;
	virtual void IsDetailWindow(bool isDetailWindow) = 0;
	virtual bool IsVisible() = 0;
	virtual BaseViewController *Controller() = 0;
};

#endif
