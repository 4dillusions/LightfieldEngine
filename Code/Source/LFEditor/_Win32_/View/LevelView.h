/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "ILevelView.h"
#include <QtWidgets/QMainWindow>
#include "ui_LevelView.h"

class LevelViewController;

class LevelView : public QMainWindow, public ILevelView
{
	Q_OBJECT

public:
	LevelView(QWidget *parent = 0);
	~LevelView() override;

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
	QGridLayout *LevelMatrixLayout() override;
	QLayout *TilesLayout() override;
	
	void ShowDialog() override;

	int LevelIndex() override;
	void LevelIndex(int levelIndex) override;
	void LevelIndexMaximum(int maximum) override;
	void LevelIndexMinimum(int minimum) override;
	int ZoomValue() override;
	void ZoomValue(int value) override;

	void ConnectTileButtonClick(const QToolButton *button) override;
	void ConnectLevelMatrixButtonClick(const QToolButton *button) override;

	void closeEvent(QCloseEvent *event);

public slots:
	void ToolButtonClick(QAction *action);
	void LevelMatrixButtonClick();
	void TileClicked();
	void LevelIndexValueChanged(int value);
	void ZoomValueChanged(int value);

private:
	Ui::LevelView ui;
	LevelViewController *controller;
	bool isModified = false;
};

#endif
