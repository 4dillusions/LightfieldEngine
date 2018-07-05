/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "MainView.h"
#include <qfile.h>
#include <qobject.h>
#include "..\Controller\MainViewController.h"

MainView::MainView(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);
	
	QFile File("LFEditor/darkorange.qss");
	File.open(QFile::ReadOnly);
	QString StyleSheet = QLatin1String(File.readAll());
	qApp->setStyleSheet(StyleSheet);

	controller = new MainViewController(this);
}

MainView::~MainView()
{
	delete controller;
}

void MainView::ShowWindow()
{
	show();
}

void MainView::MenuButtonClick()
{
	auto sender = ((QToolButton *)QObject::sender());
	auto name = sender->objectName();

	if (MenuButtonCommand != nullptr)
	{
		hide();

		if (name == ui.OptionsStateButton->objectName())
			MenuButtonCommand(MenuItems::Options);
		else if (name == ui.GameStateButton->objectName())
			MenuButtonCommand(MenuItems::GameState);
		else if (name == ui.LevelsButton->objectName())
			MenuButtonCommand(MenuItems::Level);
	}
}

#endif
