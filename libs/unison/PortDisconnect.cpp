/*
 * PortDisconnect.cpp
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


#include "unison/PortDisconnect.h"
#include "unison/ProcessingContext.h"

namespace Unison {
  namespace Internal {

PortDisconnect::PortDisconnect (Port *port1, Port *port2) :
  Command(),
  m_port1(port1),
  m_port2(port2),
  m_patch(NULL)
{
  m_blocking = false;
  m_compiled = new QList<Patch::CompiledProcessor>();
  m_state = Command::Created;
}


void PortDisconnect::preExecute ()
{
  m_patch = m_port1->parentPatch();
  Q_ASSERT(m_patch);
  // TODO Bring back this assertion once BackendPorts have a parent node
  //Q_ASSERT(m_patch == m_port2->parentPatch());
  Q_ASSERT(m_port1->isConnected(m_port2));
  Q_ASSERT(m_port2->isConnected(m_port1));

  *m_port1->_connectedPorts() -= m_port2;
  *m_port2->_connectedPorts() -= m_port1;
  
  m_patch->compile(*m_compiled);
  
  Command::preExecute();
}


void PortDisconnect::execute (ProcessingContext &context)
{
  // FIXME: Leaking m_patch->compiledProcessors();
  m_patch->setCompiledProcessors(m_compiled);
  Command::execute(context);
}


void PortDisconnect::postExecute ()
{
  Command::postExecute();
}

  } // Internal
} // Unison

// vim: ts=8 sw=2 sts=2 et sta noai
