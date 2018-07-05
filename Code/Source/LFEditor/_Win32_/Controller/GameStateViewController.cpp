/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "GameStateViewController.h"
#include "LevelViewController.h"
#include "..\Controller\ViewManager.h"
#include <qwidget.h>

using namespace LFEngine::Data;

GameStateViewController::GameStateViewController(IGameStateView *view) : view(view), BaseViewController(view)
{ 
	gameStateDataModel = new LFGameStateData();
	model = gameStateDataModel;

	view->LevelButtonCommand = std::bind(&GameStateViewController::LevelButtonCommand, this);
	ViewManager::Factory()->LevelViewItem()->CloseCommand = std::bind(&GameStateViewController::LevelCloseCommand, this, std::placeholders::_1);
}

GameStateViewController::~GameStateViewController()
{
	delete gameStateDataModel;
}

void GameStateViewController::Save()
{
	SetGameStateData();
	dynamic_cast<LevelViewController *>(ViewManager::Factory()->LevelViewItem()->Controller())->ModifyGameStateData(gameStateDataModel);

	BaseViewController::Save();
}

void GameStateViewController::SetControls()
{
	view->LevelIndex(gameStateDataModel->data.levelIndex);
	view->Second(gameStateDataModel->data.second);
	view->Lives(gameStateDataModel->data.lives);

	dynamic_cast<LevelViewController *>(ViewManager::Factory()->LevelViewItem()->Controller())->SetControls(gameStateDataModel);

	BaseViewController::SetControls();
}

void GameStateViewController::LevelButtonCommand()
{
	if (!ViewManager::Factory()->LevelViewItem()->IsVisible())
	{
		auto levelController = dynamic_cast<LevelViewController *>(ViewManager::Factory()->LevelViewItem()->Controller());

		ViewManager::Factory()->LevelViewItem()->IsDetailWindow(true);
		ViewManager::Factory()->LevelViewItem()->Title("Game State - detail");
		
		SetGameStateData();

		levelController->GameStateData(gameStateDataModel);
		ViewManager::Factory()->LevelViewItem()->ShowDialog();
		levelController->SetControls(gameStateDataModel);
	}
}

void GameStateViewController::LevelCloseCommand(QCloseEvent *event)
{
	dynamic_cast<LevelViewController *>(ViewManager::Factory()->LevelViewItem()->Controller())->ModifyGameStateData(gameStateDataModel);
}

void GameStateViewController::SetGameStateData()
{
	gameStateDataModel->data.levelIndex = view->LevelIndex();
	gameStateDataModel->data.second = view->Second();
	gameStateDataModel->data.lives = view->Lives();
}

#endif
