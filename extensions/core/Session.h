/*
 * Session.h
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

#ifndef UNISON_SESSION_H
#define UNISON_SESSION_H

#include <QList>

#include "Core_global.h"
#include "prg/Uncopyable.h"
#include "unison/ProcessingContext.h"

namespace Core {

class CompositeProcessor;
class PooledBufferProvider;
class JackEngine;
class Node;
class Processor;


/**
 * A hodgepodge of things at the moment, ultimately this will be a single
 * user's session.  Things like the active project, connection graph,
 * sequencer, and other allocated resources will be split into seperate
 * classes, but referenced from here.  A little like LMMS's Engine class except
 * theoretically multiple Sessions could possibly be open in the editor at the
 * same time. */
CORE_EXPORT class Session : PRG::Uncopyable
{
  public:
    Session (JackEngine& engine);
    ~Session ();

    // TODO: expose a generic Engine instead of JackEngine
    JackEngine& engine () const {
      return *m_engine;
    }

    BufferProvider& bufferProvider () const;

    void process (const ProcessingContext& context);

    // TODO: Compiler? Song, Sequencer, Redo/Undo, whatever..
    void hackCompile ();
    void add (Processor* processor);
    void remove (Processor* processor);

  private:
    CompositeProcessor* m_rootProcessor;
    PooledBufferProvider* m_bufferProvider;
    JackEngine* m_engine;
};

} // Core

#endif

// vim: ts=8 sw=2 sts=2 et sta noai
