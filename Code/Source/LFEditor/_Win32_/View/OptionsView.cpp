/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "OptionsView.h"
#include <qobject.h>
#include "..\Controller\OptionsViewController.h"

OptionsView::OptionsView(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	
	controller = new OptionsViewController(this);
}

OptionsView::~OptionsView()
{
	delete controller;
}

void OptionsView::ShowWindow()
{
	if (ShowCommand != nullptr)
		ShowCommand();

	show();
}

void OptionsView::HideWindow()
{
	close();
}

bool OptionsView::IsModified()
{
	return isModified;
}

void OptionsView::IsModified(bool isModified)
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

void OptionsView::Title(const QString &title)
{
	setWindowTitle(title);
}

QString OptionsView::Title()
{
	return windowTitle();
}

bool OptionsView::IsDetailWindow()
{
	return !ui.toolBar->isEnabled();
}

void OptionsView::IsDetailWindow(bool isDetailWindow)
{
	ui.toolBar->setEnabled(!isDetailWindow);
}

bool OptionsView::IsVisible()
{
	return isVisible();
}

BaseViewController *OptionsView::Controller()
{
	return controller;
}

bool OptionsView::IsMusic()
{
	return ui.IsMusicOnCheck->isChecked();
}

void OptionsView::IsMusic(bool isMusic)
{
	ui.IsMusicOnCheck->setChecked(isMusic);
}

unsigned char OptionsView::MusicVolume()
{
	return ui.MusicVolumeSlider->value();
}

void OptionsView::MusicVolume(unsigned char musicVolume)
{
	ui.MusicVolumeSlider->setValue(musicVolume);
}

bool OptionsView::IsSfx()
{
	return ui.IsSfxOnCheck->isChecked();
}

void OptionsView::IsSfx(bool isSfx)
{
	ui.IsSfxOnCheck->setChecked(isSfx);
}

unsigned char OptionsView::SfxVolume()
{
	return ui.SfxVolumeSlider->value();
}

void OptionsView::SfxVolume(unsigned char sfxVolume)
{
	ui.SfxVolumeSlider->setValue(sfxVolume);
}

void OptionsView::closeEvent(QCloseEvent *event)
{
	if (CloseCommand != nullptr)
		CloseCommand(event);

	IsDetailWindow(false);
}

void OptionsView::ToolButtonClick(QAction *action)
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

void OptionsView::ControlStateChanged()
{
	if (ControlStateChangedCommand != nullptr)
		ControlStateChangedCommand();
}

#endif
