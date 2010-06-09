/*
 * CoreExtension.cpp
 *
 * Copyright (c) 2010 Paul Giblock <pgib/at/users.sourceforge.net>
 *
 * This file is part of Unison - http://unison.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#include "CoreExtension.h"
/*
#include "editmode.h"
#include "editormanager.h"
#include "mainwindow.h"
#include "modemanager.h"
#include "fileiconprovider.h"
#include "designmode.h"
*/

#include <extensionsystem/ExtensionManager.h>

#include <QtCore/QtPlugin>
#include <QtCore/QDebug>

using namespace Core;
using namespace Core::Internal;

CoreExtension::CoreExtension()
//  m_mainWindow(new MainWindow), m_editMode(0)
{
}


CoreExtension::~CoreExtension()
{
  /*
  if (m_editMode) {
      removeObject(m_editMode);
      delete m_editMode;
  }

  if (m_designMode) {
      removeObject(m_designMode);
      delete m_designMode;
  }

  // delete FileIconProvider singleton
  delete FileIconProvider::instance();

  delete m_mainWindow;
  */
}


void CoreExtension::parseArguments(const QStringList &arguments)
{
  Q_UNUSED(arguments)
  /*
  for (int i = 0; i < arguments.size() - 1; i++) {
    if (arguments.at(i) == QLatin1String("-color")) {
      const QString colorcode(arguments.at(i + 1));
      m_mainWindow->setOverrideColor(QColor(colorcode));
      i++; // skip the argument
    }
  }
  */
}


bool CoreExtension::initialize(const QStringList &arguments, QString *errorMessage)
{
  Q_UNUSED(errorMessage);
  parseArguments(arguments);
  /*
  const bool success = m_mainWindow->init(errorMessage);
  if (success) {
    EditorManager *editorManager = m_mainWindow->editorManager();
    m_editMode = new EditMode(editorManager);
    addObject(m_editMode);

    m_designMode = new DesignMode(editorManager);
    addObject(m_designMode);
  }
  return success;
  */
  return true;
}


void CoreExtension::extensionsInitialized()
{
  //m_mainWindow->extensionsInitialized();
}


void CoreExtension::remoteCommand(const QStringList &options, const QStringList &args)
{
  Q_UNUSED(options)
  Q_UNUSED(args)
  //m_mainWindow->openFiles(args);
  //m_mainWindow->activateWindow();
}

/*
void CoreExtension::fileOpenRequest(const QString &f)
{
  remoteCommand(QStringList(), QStringList(f));
}
*/

void CoreExtension::shutdown()
{
  //m_mainWindow->shutdown();
}

EXPORT_EXTENSION(CoreExtension)

// vim: ts=8 sw=2 sts=2 et sta noai
