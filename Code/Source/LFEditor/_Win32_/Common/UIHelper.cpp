/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#include "UIHelper.h"
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qlayout.h>

int UIHelper::ShowDontSavedDialog()
{
	QMessageBox msgBox;
	msgBox.setText("The document has been modified.");
	msgBox.setInformativeText("Do you want to save your changes?");
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setDefaultButton(QMessageBox::Yes);

	return msgBox.exec();
}

void UIHelper::ShowDialog(const QString &message, bool isError)
{
	QMessageBox msgBox;
	msgBox.setText(message);
	msgBox.setIcon(isError ? QMessageBox::Critical : QMessageBox::Information);
	msgBox.exec();
}

QString UIHelper::OpenFileDialog(QWidget *view, const QString &title, const QString &extension)
{
	return QFileDialog::getOpenFileName(view, title, "", "Files (*" + extension + ")");
}

QString UIHelper::NewFileDialog(QWidget *view, const QString &title, const QString &extension)
{
	return QFileDialog::getSaveFileName(view, title, "", "Files (*" + extension + ")");
}

void UIHelper::ClearLayout(QLayout *layout)
{
	while (QLayoutItem* item = layout->takeAt(0))
	{
		if (QWidget* widget = item->widget())
			delete widget;
	}
}

#endif
