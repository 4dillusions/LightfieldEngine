/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include "IBaseView.h"

class QGridLayout;
class QLayout;
class QToolButton;
class QComboBox;

namespace LFEngine  { namespace Data
{
	class LFGameStateData;
}}

class ILevelView : public IBaseView
{
public:
	virtual ~ILevelView() { };

	std::function<void(QToolButton *sender)> TileButtonCommand = nullptr;
	std::function<void(QToolButton *sender)> LevelMatrixButtonCommand = nullptr;
	std::function<void(int value)> LevelIndexChangedCommand = nullptr;

	virtual QGridLayout *LevelMatrixLayout() = 0;
	virtual QLayout *TilesLayout() = 0;

	virtual void ShowDialog() = 0;

	virtual int LevelIndex() = 0;
	virtual void LevelIndex(int levelIndex) = 0;
	virtual void LevelIndexMaximum(int maximum) = 0;
	virtual void LevelIndexMinimum(int minimum) = 0;
	virtual int ZoomValue() = 0;
	virtual void ZoomValue(int value) = 0;

	virtual void ConnectTileButtonClick(const QToolButton *button) = 0;
	virtual void ConnectLevelMatrixButtonClick(const QToolButton *button) = 0;
};

#endif
