/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "GameStateView.h"
#include <qobject.h>
#include "..\Controller\GameStateViewController.h"
#include "..\Controller\ViewManager.h"

GameStateView::GameStateView(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	
	controller = new GameStateViewController(this);
}

GameStateView::~GameStateView()
{
	delete controller;
}

void GameStateView::ShowWindow()
{
	if (ShowCommand != nullptr)
		ShowCommand();

	show();
}

void GameStateView::HideWindow()
{
	close();
}

bool GameStateView::IsModified()
{
	return isModified;
}

void GameStateView::IsModified(bool isModified)
{
	this->isModified = isModified;
	ui.ActionSave->setEnabled(isModified);

	if (isModified)
	{
		if (!windowTitle().endsWith("*"))
			setWindowTitle(windowTitle() + "*");
	}
	else
		setWindowTitle(windowTitle().remove("*"));
}

void GameStateView::Title(const QString &title)
{
	setWindowTitle(title);
}

QString GameStateView::Title()
{
	return windowTitle();
}

bool GameStateView::IsDetailWindow()
{
	return !ui.toolBar->isEnabled();
}

void GameStateView::IsDetailWindow(bool isDetailWindow)
{
	ui.toolBar->setEnabled(!isDetailWindow);
}

bool GameStateView::IsVisible()
{
	return isVisible();
}

BaseViewController *GameStateView::Controller()
{
	return controller;
}

unsigned char GameStateView::LevelIndex()
{
	return ui.LevelIndexSpin->value();
}

void GameStateView::LevelIndex(unsigned char levelIndex)
{
	ui.LevelIndexSpin->setValue(levelIndex);
}

unsigned short GameStateView::Second()
{
	return ui.SecondSpin->value();
}

void GameStateView::Second(unsigned short second)
{
	ui.SecondSpin->setValue(second);
}

unsigned short GameStateView::Lives()
{
	return ui.LivesSpin->value();
}

void GameStateView::Lives(unsigned short lives)
{
	ui.LivesSpin->setValue(lives);
}

void GameStateView::closeEvent(QCloseEvent *event)
{
	if (CloseCommand != nullptr)
		CloseCommand(event);

	if (ViewManager::Factory()->LevelViewItem()->IsVisible())
	{
		ViewManager::Factory()->LevelViewItem()->HideWindow();
		IsDetailWindow(false);
	}
}

void GameStateView::ToolButtonClick(QAction *action)
{
	if (ToolButtonCommand != nullptr)
	{
		if (action->objectName() == ui.ActionNew->objectName())
			ToolButtonCommand(ToolbarItems::New);
		else if (action->objectName() == ui.ActionOpen->objectName())
			ToolButtonCommand(ToolbarItems::Open);
		else if (action->objectName() == ui.ActionSave->objectName())
			ToolButtonCommand(ToolbarItems::Save);
	}
}

void GameStateView::LevelButtonClick()
{
	if (LevelButtonCommand != nullptr)
		LevelButtonCommand();
}

void GameStateView::ControlStateChanged()
{
	if (ControlStateChangedCommand != nullptr)
		ControlStateChangedCommand();
}

#endif
