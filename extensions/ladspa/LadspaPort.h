/*
 * LadspaPort.h
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

#ifndef UNISON_LADSPA_PORT_H
#define UNISON_LADSPA_PORT_H

#include "LadspaPlugin.h"

#include <unison/Port.h>
#include <unison/types.h>

#include <slv2/slv2.h>

namespace Ladspa {
  namespace Internal {

/** A Port on a plugin.  I wonder if we should be calling slv2 functions, or
 *  maybe we should just copy all the data into the class?  Another idea is a
 *  PluginPort that does index-based accesses on a Plugin.  No Port subclass
 *  is needed for Ladspa, VST, DSSI, plugins..
 *  Overall, LadspaPort does alot of stuff that should be reused when
 *  implementing ports for other processor types (VST etc..) */
class LadspaPort : public Unison::Port
{
  public:
    LadspaPort (const LadspaWorld & world, LadspaPlugin * plugin, uint32_t index);

    ~LadspaPort ();

    QString id () const;
    QString name () const;
    Unison::PortType type () const;
    Unison::PortDirection direction () const;

    float value () const;
    void setValue (float value);

    float defaultValue () const
    {
      return m_defaultValue;
    }

    bool isBounded () const
    {
      return true;
    }

    float minimum () const
    {
      return m_min;
    }

    float maximum () const
    {
      return m_max;
    }

    bool isToggled () const
    {
      return slv2_port_has_property( m_plugin->slv2Plugin(),
                                     m_port, m_world.toggled );
    }

    Node* parent () const;
    const QSet<Unison::Node* const> interfacedNodes () const;

    void connectToBuffer ();


  private:
    LadspaPlugin * m_plugin;
    SLV2Port m_port;
    uint32_t m_index;

    float m_value;
    float m_defaultValue;
    float m_min;
    float m_max;
    bool  m_isSampleRate;
};

  } // Internal
} // Ladspa

#endif

// vim: ts=8 sw=2 sts=2 et sta noai
