/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\View\IOptionsView.h"
#include "BaseViewController.h"
#include "..\..\..\Engine\Data\LFOptionsData.h"

class OptionsViewController : public BaseViewController
{
public:
	OptionsViewController(IOptionsView *view);
	~OptionsViewController() override;
	
	void Save() override;
	void SetControls() override;

private:
	IOptionsView *view;
	LFEngine::Data::LFOptionsData *optionsDataModel;
};

#endif
