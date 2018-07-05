/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "LevelOptionsView.h"
#include "..\Common\Constants.h"
#include <qobject.h>

using namespace LFEngine::Data;

LevelOptionsView::LevelOptionsView(QWidget *parent) : QDialog(parent)
{
	ui.setupUi(this);

	InitControls();
}

LevelOptionsView::~LevelOptionsView()
{ }

void LevelOptionsView::InitControls()
{
	ui.TilesCombo->addItems(tilesetList);
}

void LevelOptionsView::SetLevelData(LFLevelData *levelDataModel, bool isRead)
{
	ui.TilesCombo->setEnabled(true);
	ui.LevelCountSpin->setEnabled(true);
	ui.SizeXSpin->setEnabled(true);
	ui.SizeYSpin->setEnabled(true);

	if (isRead) //read - from data and set UI
	{
		ui.TilesCombo->setCurrentIndex(levelDataModel->data.editorData.tilesId);
		ui.SizeXSpin->setValue(levelDataModel->data.editorData.levelSizeX);
		ui.SizeYSpin->setValue(levelDataModel->data.editorData.levelSizeY);
		ui.LevelCountSpin->setValue(levelDataModel->data.levelCount);
	}
	else //write - to data from UI
	{
		levelDataModel->data.editorData.tilesId = ui.TilesCombo->currentIndex();
		levelDataModel->data.editorData.levelSizeX = ui.SizeXSpin->value();
		levelDataModel->data.editorData.levelSizeY = ui.SizeYSpin->value();
		levelDataModel->data.levelCount = ui.LevelCountSpin->value();
	}
}

void LevelOptionsView::SetLevelData(LFGameStateData *gameStateDataModel, bool isRead)
{
	if (isRead) //read - from data and set UI
	{
		ui.TilesCombo->setCurrentIndex(gameStateDataModel->data.editorData.tilesId);
		ui.SizeXSpin->setValue(gameStateDataModel->data.editorData.levelSizeX);
		ui.SizeYSpin->setValue(gameStateDataModel->data.editorData.levelSizeY);
		
	}
	else //write - to data from UI
	{
		gameStateDataModel->data.editorData.tilesId = ui.TilesCombo->currentIndex();
		gameStateDataModel->data.editorData.levelSizeX = ui.SizeXSpin->value();
		gameStateDataModel->data.editorData.levelSizeY = ui.SizeYSpin->value();
	}

	ui.TilesCombo->setEnabled(false);
	ui.LevelCountSpin->setEnabled(false);
	ui.SizeXSpin->setEnabled(false);
	ui.SizeYSpin->setEnabled(false);
}

#endif
