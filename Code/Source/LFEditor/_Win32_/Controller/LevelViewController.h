/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\View\ILevelView.h"
#include "BaseViewController.h"
#include "..\..\..\Engine\Data\LFLevelData.h"
#include "..\..\..\Engine\Data\LFGameStateData.h"

class QToolButton;

class LevelViewController : public BaseViewController
{
public:
	LevelViewController(ILevelView *view);
	~LevelViewController() override;

	void GameStateData(LFEngine::Data::LFGameStateData *gameStateData);

	void Save() override;
	void SetControls() override;
	
	void SetControls(const LFEngine::Data::LFGameStateData *gameStateDataModel);
	void ModifyGameStateData(LFEngine::Data::LFGameStateData *gameStateDataModel);

	void TileButtonCommand(QToolButton *sender);
	void LevelMatrixButtonCommand(QToolButton *sender);
	void LevelIndexChangedCommand(int value);

	void ShowLevelOptionsDialog();

private:
	ILevelView *view;
	LFEngine::Data::LFLevelData *levelDataModel;
	LFEngine::Data::LFGameStateData *gameStateData;
	QToolButton *selectedTile = nullptr;
	QList<QIcon> iconList;

	void RecreateTiles(); //create tiles from tilesID and tileset folder
	void RecreateLevelMatrix(const LFEngine::Data::LFGameStateData *gameStateDataModel = nullptr); //recreate level matrix from level data (gameStateDataModel = nullptr) or game state data	
	void SetLevelMatrix(int levelIndex); //set level matrix from level data
};

#endif
