/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\View\IGameStateView.h"
#include "BaseViewController.h"
#include "..\..\..\Engine\Data\LFGameStateData.h"

class GameStateViewController : public BaseViewController
{
public:
	GameStateViewController(IGameStateView *view);
	~GameStateViewController() override;

	void Save() override;
	void SetControls() override;

	void LevelButtonCommand();
	void LevelCloseCommand(QCloseEvent *event);

private:
	IGameStateView *view;
	LFEngine::Data::LFGameStateData *gameStateDataModel;

	void SetGameStateData(); //set game state data from UI
};

#endif
