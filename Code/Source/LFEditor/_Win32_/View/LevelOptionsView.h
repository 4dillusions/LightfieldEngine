/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\..\..\Engine\Data\LFLevelData.h"
#include "..\..\..\Engine\Data\LFGameStateData.h"
#include <QtWidgets/QDialog>
#include "ui_LevelOptionsView.h"

class LevelOptionsView : public QDialog
{
	Q_OBJECT

public:
	LevelOptionsView(QWidget *parent = 0);
	~LevelOptionsView();

	void InitControls();
	void SetLevelData(LFEngine::Data::LFLevelData *levelDataModel, bool isRead); //read - from data and set UI, write - to data from UI
	void SetLevelData(LFEngine::Data::LFGameStateData *gameStateDataModel, bool isRead); //read - from data and set UI, write - to data from UI

private:
	Ui::LevelOptionsView ui;
};

#endif
