/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "OptionsViewController.h"
#include "..\Controller\ViewManager.h"

using namespace LFEngine::Data;

OptionsViewController::OptionsViewController(IOptionsView *view) : view(view), BaseViewController(view)
{ 
	optionsDataModel = new LFOptionsData();
	model = optionsDataModel;
}

OptionsViewController::~OptionsViewController()
{
	delete optionsDataModel;
}

void OptionsViewController::Save()
{
	optionsDataModel->data.isMusicOn = view->IsMusic();
	optionsDataModel->data.volumeMusic = view->MusicVolume();
	optionsDataModel->data.isSFXOn = view->IsSfx();
	optionsDataModel->data.volumeSFX = view->SfxVolume();

	BaseViewController::Save();
}

void OptionsViewController::SetControls()
{
	view->IsMusic(optionsDataModel->data.isMusicOn);
	view->MusicVolume(optionsDataModel->data.volumeMusic);
	view->IsSfx(optionsDataModel->data.isSFXOn);
	view->SfxVolume(optionsDataModel->data.volumeSFX);

	BaseViewController::SetControls();
}

#endif
