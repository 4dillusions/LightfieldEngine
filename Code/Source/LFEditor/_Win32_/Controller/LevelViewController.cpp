/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LevelViewController.h"
#include "..\Controller\ViewManager.h"
#include "..\View\LevelView.h"
#include "..\View\LevelOptionsView.h"
#include "..\Common\UIHelper.h"
#include "..\Common\Constants.h"
#include <qdir.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qapplication.h>
#include <qobject.h>

using namespace LFEngine::Data;

LevelViewController::LevelViewController(ILevelView *view) : view(view), BaseViewController(view)
{ 
	levelDataModel = new LFLevelData();
	model = levelDataModel;

	view->TileButtonCommand = std::bind(&LevelViewController::TileButtonCommand, this, std::placeholders::_1);
	view->LevelMatrixButtonCommand = std::bind(&LevelViewController::LevelMatrixButtonCommand, this, std::placeholders::_1);
	view->LevelIndexChangedCommand = std::bind(&LevelViewController::LevelIndexChangedCommand, this, std::placeholders::_1);
}

LevelViewController::~LevelViewController()
{
	delete levelDataModel;
}

void LevelViewController::GameStateData(LFGameStateData *gameStateData)
{
	this->gameStateData = gameStateData;
}

void LevelViewController::Save()
{
	levelDataModel->data.editorData.zoom = view->ZoomValue();
	
	BaseViewController::Save();
}

void LevelViewController::SetControls()
{
	view->LevelIndex(0);

	view->LevelIndexMaximum(levelDataModel->data.levelCount - 1);
	view->LevelIndexMinimum(0);
	RecreateTiles();
	RecreateLevelMatrix();
	view->ZoomValue(levelDataModel->data.editorData.zoom);	

	BaseViewController::SetControls();
}

void LevelViewController::SetControls(const LFGameStateData *gameStateDataModel)
{
	view->LevelIndex(0);

	view->LevelIndexMaximum(gameStateDataModel->data.levelIndex);
	view->LevelIndexMinimum(0);
	view->LevelIndex(gameStateDataModel->data.levelIndex);
	RecreateTiles();
	RecreateLevelMatrix(gameStateDataModel);
	view->ZoomValue(gameStateDataModel->data.editorData.zoom);
}

void LevelViewController::ModifyGameStateData(LFGameStateData *gameStateDataModel)
{
	gameStateDataModel->data.editorData.zoom = view->ZoomValue();
	gameStateDataModel = gameStateData;
}

void LevelViewController::TileButtonCommand(QToolButton *sender)
{
	if (selectedTile != nullptr)
	{
		selectedTile->setChecked(false);
		selectedTile->setEnabled(true);
	}

	selectedTile = sender;
	selectedTile->setEnabled(false);
}

void LevelViewController::LevelMatrixButtonCommand(QToolButton *sender)
{
	if (selectedTile != nullptr)
	{
		sender->setIcon(selectedTile->icon());
		sender->setText(selectedTile->text());
	}

	int x, y, xSpan, ySpan;
	view->LevelMatrixLayout()->getItemPosition(view->LevelMatrixLayout()->indexOf(sender), &y, &x, &ySpan, &xSpan);

	if (view->IsDetailWindow())	
		gameStateData->data.levelMatrix[x][y] = sender->text().toInt() - 1;
	else 
		levelDataModel->data.levelMatrix[view->LevelIndex()][x][y] = sender->text().toInt() - 1;
}

void LevelViewController::LevelIndexChangedCommand(int value)
{
	SetLevelMatrix(value);
}

void LevelViewController::ShowLevelOptionsDialog()
{
	LevelOptionsView levelOptionsdialog;

	if (view->IsDetailWindow())
		levelOptionsdialog.SetLevelData(gameStateData, true);
	else
		levelOptionsdialog.SetLevelData(levelDataModel, true);

	levelOptionsdialog.exec();

	if (view->IsDetailWindow())
		levelOptionsdialog.SetLevelData(gameStateData, false);
	else
		levelOptionsdialog.SetLevelData(levelDataModel, false);
}

void LevelViewController::RecreateTiles()
{
	QApplication::setOverrideCursor(Qt::CursorShape::WaitCursor);

	UIHelper::ClearLayout(view->TilesLayout());
	iconList.clear();
	selectedTile = nullptr;

	int tilesId = (view->IsDetailWindow()) ? gameStateData->data.editorData.tilesId : levelDataModel->data.editorData.tilesId;
	QString folder = editorFolder + "/" + tilesetList[tilesId];
	QDir dir(folder);
	auto fileList = dir.entryList(QDir::Filter::Files, QDir::SortFlag::Name);

	foreach(const QString &fileName, fileList) 
	{
		if (fileName.endsWith(editorTileExtension))
		{
			QIcon icon(folder + "/" + fileName);
			iconList.append(icon);

			auto button = new QToolButton();
			
			button->setMinimumSize(buttonSize);
			button->setMaximumSize(buttonSize);
			button->setCheckable(true);
			button->setChecked(false);
			button->setAutoRaise(false);
			button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);
			button->setIcon(icon);
			button->setIconSize(buttonSize);
			button->setText(QString(fileName).remove(editorTileExtension));
			
			view->ConnectTileButtonClick(button);
			view->TilesLayout()->addWidget(button);
		}
	}

	if (view->TilesLayout()->count() > 0)
		dynamic_cast<QToolButton *>(view->TilesLayout()->itemAt(0)->widget())->click();
		
	QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}

void LevelViewController::RecreateLevelMatrix(const LFGameStateData *gameStateDataModel)
{
	QApplication::setOverrideCursor(Qt::CursorShape::WaitCursor);

	int levelSizeX = gameStateDataModel == nullptr ? levelDataModel->data.editorData.levelSizeX : gameStateDataModel->data.editorData.levelSizeX;
	int levelSizeY = gameStateDataModel == nullptr ? levelDataModel->data.editorData.levelSizeY : gameStateDataModel->data.editorData.levelSizeY;

	UIHelper::ClearLayout(view->LevelMatrixLayout());
	for (int x = 0; x < levelSizeX; x++)
		for (int y = 0; y < levelSizeY; y++)
		{
			auto button = new QToolButton();

			button->setMinimumSize(buttonSize / 10);
			button->setMaximumSize(buttonSize / 10);
			button->setAutoRaise(false);
			button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonIconOnly);

			if (gameStateDataModel == nullptr)
			{
				if (iconList.count() > levelDataModel->data.levelMatrix[view->LevelIndex()][x][y])
					button->setIcon(iconList[levelDataModel->data.levelMatrix[view->LevelIndex()][x][y]]);
			}
			else
			{
				if (iconList.count() > gameStateDataModel->data.levelMatrix[x][y])
					button->setIcon(iconList[gameStateDataModel->data.levelMatrix[x][y]]);
			}

			button->setIconSize(buttonSize);

			view->ConnectLevelMatrixButtonClick(button);
			view->LevelMatrixLayout()->addWidget(button, y, x);
		}

	QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}

void LevelViewController::SetLevelMatrix(int levelIndex)
{
	QApplication::setOverrideCursor(Qt::CursorShape::WaitCursor);

	if (view->LevelMatrixLayout()->count() == levelDataModel->data.editorData.levelSizeX * levelDataModel->data.editorData.levelSizeY)
		for (int y = 0; y < levelDataModel->data.editorData.levelSizeY; y++)
			for (int x = 0; x < levelDataModel->data.editorData.levelSizeX; x++)
				if (iconList.count() > levelDataModel->data.levelMatrix[levelIndex][x][y])
					dynamic_cast<QToolButton *>(view->LevelMatrixLayout()->itemAtPosition(y, x)->widget())->setIcon(iconList[levelDataModel->data.levelMatrix[levelIndex][x][y]]);

	QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
}

#endif
