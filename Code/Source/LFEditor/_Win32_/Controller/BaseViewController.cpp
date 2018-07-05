/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "BaseViewController.h"
#include "ViewManager.h"
#include "LevelViewController.h"
#include "..\Common\UIHelper.h"
#include "..\Common\Constants.h"
#include "..\..\..\Engine\Common\LFExtensions.h"
#include <qmessagebox.h>

BaseViewController::BaseViewController(IBaseView *view) : view(view)
{ 
	view->CloseCommand = std::bind(&BaseViewController::CloseCommand, this, std::placeholders::_1);
	view->ShowCommand = std::bind(&BaseViewController::ShowCommand, this);
	view->ToolButtonCommand = std::bind(&BaseViewController::ToolButtonCommand, this, std::placeholders::_1);
	view->ControlStateChangedCommand = std::bind(&BaseViewController::ControlStateChangedCommand, this);
}

void BaseViewController::ShowCommand()
{
	Reset();
}

void BaseViewController::CloseCommand(QCloseEvent *event)
{
	if (view->IsModified())
	{
		switch (UIHelper::ShowDontSavedDialog())
		{
		case QMessageBox::Yes:
			BaseSave();
			ViewManager::Factory()->MainViewItem()->ShowWindow();
			event->accept();
			break;

		case QMessageBox::No:
			ViewManager::Factory()->MainViewItem()->ShowWindow();
			event->accept();
			break;

		case QMessageBox::Cancel:
			event->ignore();
			break;

		default:
			event->ignore();
			break;
		}
	}
	else
	{
		if (!view->IsDetailWindow())
			ViewManager::Factory()->MainViewItem()->ShowWindow();

		event->accept();
	}
}

void BaseViewController::ToolButtonCommand(ToolbarItems toolBarItem)
{
	QString fileName = "";

	switch (toolBarItem)
	{
	case ToolbarItems::New:
		fileName = NewDialog();
		if (fileName != "")
		{
			if (view->IsModified())
			{
				switch (UIHelper::ShowDontSavedDialog())
				{
				case QMessageBox::Yes:
					BaseSave();
					Reset();
					New(fileName);
					break;

				case QMessageBox::No:
					Reset();
					New(fileName);
					break;
				}
			}
			else
			{
				Reset();
				New(fileName);
			}
		}
		break;

	case ToolbarItems::Open:
		fileName = OpenDialog();
		if (fileName != "")
		{
			if (view->IsModified())
			{
				switch (UIHelper::ShowDontSavedDialog())
				{
				case QMessageBox::Yes:
					BaseSave();
					Reset();
					Open(fileName);
					break;

				case QMessageBox::No:
					Open(fileName);
					break;
				}
			}
			else
			{
				Open(fileName);
			}
		}
		break;

	case ToolbarItems::Save:
		BaseSave();
		break;
	}
}

void BaseViewController::ControlStateChangedCommand()
{
	view->IsModified(true);
}

void BaseViewController::Save()
{
	model->Save(fileName.toStdString().c_str());

	view->IsModified(false);
}

void BaseViewController::SetControls()
{
	view->IsModified(false);
}

void BaseViewController::Reset()
{
	model->Reset();

	view->Title(DefaultTitle);
	view->IsModified(false);
	fileName.clear();

	if (auto controller = dynamic_cast<LevelViewController *>(this))
		controller->ShowLevelOptionsDialog();
	
	SetControls();
}

void BaseViewController::New(const QString &fileName)
{
	model->Save(fileName.toStdString().c_str());

	this->fileName = fileName;
	SetTitleFromFileName(fileName);
	view->IsModified(false);
}

void BaseViewController::Open(const QString &fileName)
{
	if (model->Load(fileName.toStdString().c_str()))
	{
		this->fileName = fileName;
		SetTitleFromFileName(fileName);
		SetControls();
	}
	else
		UIHelper::ShowDialog("This data file \"" + fileName + "\" wrong or incompatible!", true);
}

QString BaseViewController::NewDialog()
{
	auto window = dynamic_cast<QWidget *>(view);

	return UIHelper::NewFileDialog(window, ("Save new " + window->objectName().remove("View") + " data file"), LFDataExtension);
}

QString BaseViewController::OpenDialog()
{
	auto window = dynamic_cast<QWidget *>(view);

	return UIHelper::OpenFileDialog(window, ("Open " + window->objectName().remove("View") + " data file"), LFDataExtension);
}

void BaseViewController::SetTitleFromFileName(const QString &fileName)
{
	auto title = fileName.split("/");
	view->Title(title.last().remove(LFDataExtension));
}

void BaseViewController::BaseSave()
{
	if (view->Title().startsWith(DefaultTitle))
	{
		fileName = NewDialog();
		if (fileName != "")
		{
			New(fileName);
			Save();
		}
	}
	else
		Save();
}

#endif
