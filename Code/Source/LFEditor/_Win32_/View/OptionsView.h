/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IOptionsView.h"
#include <QtWidgets/QMainWindow>
#include "ui_OptionsView.h"

class OptionsViewController;

class OptionsView : public QMainWindow, public IOptionsView
{
	Q_OBJECT

public:
	OptionsView(QWidget *parent = 0);
	~OptionsView() override;

	void ShowWindow() override;
	void HideWindow() override;
	bool IsModified() override;
	void IsModified(bool isModified) override;
	void Title(const QString &title) override;
	QString Title() override;
	bool IsDetailWindow() override;
	void IsDetailWindow(bool isDetailWindow) override;
	bool IsVisible() override;
	BaseViewController *Controller() override;

	bool IsMusic() override;
	void IsMusic(bool isMusic) override;
	unsigned char MusicVolume() override;
	void MusicVolume(unsigned char musicVolume) override;
	bool IsSfx() override;
	void IsSfx(bool isSfx) override;
	unsigned char SfxVolume() override;
	void SfxVolume(unsigned char sfxVolume) override;

	void closeEvent(QCloseEvent *event);

public slots:
	void ToolButtonClick(QAction *action);
	void ControlStateChanged();

private:
	Ui::OptionsView ui;
	OptionsViewController *controller;
	bool isModified = false;
};

#endif
