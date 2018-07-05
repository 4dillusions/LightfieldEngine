/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include<qstring.h>

class QWidget;
class QLayout;

class UIHelper
{
public:
	static int ShowDontSavedDialog();
	static void ShowDialog(const QString &message, bool isError);
	static QString OpenFileDialog(QWidget *view, const QString &title, const QString &extension);
	static QString NewFileDialog(QWidget *view, const QString &title, const QString &extension);

	static void ClearLayout(QLayout *layout);
};

#endif
