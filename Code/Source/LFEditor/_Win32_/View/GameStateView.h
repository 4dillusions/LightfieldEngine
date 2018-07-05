/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IGameStateView.h"
#include <QtWidgets/QMainWindow>
#include "ui_GameStateView.h"

class GameStateViewController;

class GameStateView : public QMainWindow, public IGameStateView
{
	Q_OBJECT

public:
	GameStateView(QWidget *parent = 0);
	~GameStateView() override;

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

	virtual unsigned char LevelIndex() override;
	virtual void LevelIndex(unsigned char levelIndex) override;
	virtual unsigned short Second() override;
	virtual void Second(unsigned short second) override;
	virtual unsigned short Lives() override;
	virtual void Lives(unsigned short lives) override;

	void closeEvent(QCloseEvent *event);

public slots:
	void ToolButtonClick(QAction *action);
	void LevelButtonClick();
	void ControlStateChanged();

private:
	Ui::GameStateView ui;
	GameStateViewController *controller;
	bool isModified = false;
};

#endif
