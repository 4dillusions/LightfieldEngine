/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IMainView.h"
#include <QtWidgets/QMainWindow>
#include "ui_MainView.h"

class MainViewController;

class MainView : public QMainWindow, public IMainView
{
	Q_OBJECT

public:
	MainView(QWidget *parent = 0);
	~MainView() override;

	void ShowWindow() override;

public slots:
	void MenuButtonClick();

private:
	Ui::MainViewClass ui;
	MainViewController *controller;
};

#endif
