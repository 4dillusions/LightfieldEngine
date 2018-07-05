/*
Copyright (c) by 4D Illusions. All rights reserved.
Released under the terms of the GNU General Public License version 3 or later.
*/

#ifdef WIN32

#pragma once

#include <qstring.h>
#include <qsize.h>

static const QStringList tilesetList = QStringList() << "Lightfield2" << "MagicSnake" << "DroidBlocks";
static const QStringList atlasList = QStringList() << "" << "Placeholder" << "Wall" << "Player" << "Enemy";
static const QSize buttonSize = QSize(100, 100);
static const QString editorFolder("LFEditor/Tileset");
static const QString editorTileExtension(".jpg");

#endif
