/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "..\View\IBaseView.h"
#include "..\..\..\Engine\Data\LFIData.h"

#define DefaultTitle "Untitled"

class BaseViewController
{
public:
	BaseViewController(IBaseView *view);
	virtual ~BaseViewController() { };

	void ShowCommand();
	void CloseCommand(QCloseEvent *event);
	void ToolButtonCommand(ToolbarItems toolBarItem);
	void ControlStateChangedCommand();
	
	virtual void Save(); //save memory object to opened file	
	virtual void SetControls(); //set controls from memory object

protected:
	QString fileName;
	LFEngine::Data::LFIData *model;

private:
	IBaseView *view;

	void Reset(); //reset memory object and controls
	void New(const QString &fileName); //save memory object to new file
	void Open(const QString &fileName); //load memory object from selected file
	QString NewDialog();
	QString OpenDialog();
	void SetTitleFromFileName(const QString &fileName);
	void BaseSave();
};

#endif
