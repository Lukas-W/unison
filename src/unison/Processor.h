/*
 * Processor.h
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


#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "unison/Node.h"
#include "unison/Port.h"

namespace Unison {

class ProcessingContext;

/** Interface for all Nodes that need to have some degree of processing
 *  performed on them.
 *  TODO: We probably want to add a StandardProcessor abstract class that handles
 *  most features that don't vary across different Node classes. */

class Processor : public Node {
  public:
    virtual ~Processor () {};

    /** @return the total number of ports of all kinds */
    virtual int portCount () const = 0;

    /* TODO: Return Port* or shared pointer? */
    virtual Port* port (int idx) const = 0;

    virtual void activate () = 0;
    virtual void deactivate () = 0;

    virtual void process (const ProcessingContext & context) = 0;
    bool isVisited()   { return m_visited; };
    void visit()       { m_visited = true; };
	void unvisit()     { m_visited = false; };

  private:
    bool m_visited;
};

} // Unison

#endif // PROCESSOR_H

// vim: et ts=8 sw=2 sts=2 noai
