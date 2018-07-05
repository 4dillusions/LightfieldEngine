/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LevelView.h"
#include "..\Controller\LevelViewController.h"
#include "..\Common\Constants.h"
#include "..\..\..\Engine\Data\LFGameStateData.h"
#include <qobject.h>
#include <qlayout.h>
#include <qtoolbutton.h>
#include <qcombobox.h>

using namespace LFEngine::Data;

LevelView::LevelView(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	controller = new LevelViewController(this);
}

LevelView::~LevelView()
{
	delete controller;
}

void LevelView::ShowWindow()
{
	if (ShowCommand != nullptr)
		ShowCommand();

	setWindowModality(Qt::WindowModality::NonModal);
	show();
}

void LevelView::HideWindow()
{
	close();
}

bool LevelView::IsModified()
{
	return isModified;
}

void LevelView::IsModified(bool isModified)
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

void LevelView::Title(const QString &title)
{
	setWindowTitle(title);
}

QString LevelView::Title()
{
	return windowTitle();
}

bool LevelView::IsDetailWindow()
{
	return !ui.toolBar->isEnabled();
}

void LevelView::IsDetailWindow(bool isDetailWindow)
{
	ui.toolBar->setEnabled(!isDetailWindow);
	ui.LevelIndexSpin->setEnabled(!isDetailWindow);
}

bool LevelView::IsVisible()
{
	return isVisible();
}

BaseViewController *LevelView::Controller()
{
	return controller;
}

QGridLayout *LevelView::LevelMatrixLayout()
{
	return dynamic_cast<QGridLayout *>(ui.LevelMatrixGridLayout->layout());
}

QLayout *LevelView::TilesLayout()
{
	return ui.TilesVerticalLayout->layout();
}

void LevelView::ShowDialog()
{
	if (ShowCommand != nullptr)
		ShowCommand();

	setWindowModality(Qt::WindowModality::ApplicationModal);
	show();
}

int LevelView::LevelIndex()
{
	return ui.LevelIndexSpin->value();
}

void LevelView::LevelIndex(int levelIndex)
{
	ui.LevelIndexSpin->setValue(levelIndex);
}

void LevelView::LevelIndexMaximum(int maximum)
{
	ui.LevelIndexSpin->setMaximum(maximum);
}

void LevelView::LevelIndexMinimum(int minimum)
{
	ui.LevelIndexSpin->setMinimum(minimum);
}

int LevelView::ZoomValue()
{
	return ui.ZoomSlider->value();
}

void LevelView::ZoomValue(int value)
{
	int prevValue = ZoomValue();
	ui.ZoomSlider->setValue(value);

	if (value == prevValue)
		ZoomValueChanged(value);
}

void LevelView::ConnectTileButtonClick(const QToolButton *button)
{
	QObject::connect(button, SIGNAL(clicked()), this, SLOT(TileClicked()));
}

void LevelView::ConnectLevelMatrixButtonClick(const QToolButton *button)
{
	QObject::connect(button, SIGNAL(clicked()), this, SLOT(LevelMatrixButtonClick()));
}

void LevelView::closeEvent(QCloseEvent *event)
{
	if (CloseCommand != nullptr)
		CloseCommand(event);

	IsDetailWindow(false);
}

void LevelView::ToolButtonClick(QAction *action)
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

void LevelView::LevelMatrixButtonClick()
{
	if (LevelMatrixButtonCommand != nullptr)
		LevelMatrixButtonCommand(dynamic_cast<QToolButton *>(QObject::sender()));

	if (!IsDetailWindow())
		IsModified(true);
}

void LevelView::TileClicked()
{
	if (TileButtonCommand != nullptr)
		TileButtonCommand(dynamic_cast<QToolButton *>(QObject::sender()));
}

void LevelView::LevelIndexValueChanged(int value)
{
	if (LevelIndexChangedCommand != nullptr && !IsDetailWindow())
		LevelIndexChangedCommand(value);
}

void LevelView::ZoomValueChanged(int value)
{
	for (int i = 0; i < LevelMatrixLayout()->count(); i++)
	{
		auto button = dynamic_cast<QToolButton *>(LevelMatrixLayout()->itemAt(i)->widget());
		
		button->setMaximumSize((buttonSize.width() * value) / ui.ZoomSlider->maximum(), (buttonSize.height() * value) / ui.ZoomSlider->maximum());
		button->setMinimumSize((buttonSize.width() * value) / ui.ZoomSlider->maximum(), (buttonSize.height() * value) / ui.ZoomSlider->maximum());
	}
}

#endif
