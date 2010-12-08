/*
 * SndFileBufferReader.h
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

#ifndef UNISON_SNDFILE_BUFFER_READER_H
#define UNISON_SNDFILE_BUFFER_READER_H

#include "SndFile_global.h"

#include <core/ISampleBufferReader.h>
#include <QObject>

namespace SndFile {
namespace Internal {

/**
 * Provides an interface for readers capable of reading SampleBuffers from a
 * QFile.  Ideally, we can expand this to work for QIODevices in general!  Any
 * extensions wishing to implement this functionality must add their
 * implemenation to ExtensionManager with addObject(), the implementation will
 * then be used by PluginManager.
 * All ISampleBufferReader implementations MUST be reentrant.*/
class SndFileBufferReader : public Core::ISampleBufferReader
{
  Q_OBJECT
  public:
    SndFileBufferReader (QObject *parent = 0) :
      Core::ISampleBufferReader(parent)
    {};

    ~SndFileBufferReader ()
    {};

    QString displayName ()
    {
      return "libsndfile buffer reader.";
    };

    /**
     * Read a SampleBuffer out of the given filename.  The function returns
     * null if the file cannot be read (due to improper mime-type,
     * corrupt/improper data, IO error, etc.) 
     *
     * @param fileName the name of the file to attempt reading.
     * @return non-zero pointer on success, null on failure */
    Unison::SampleBuffer *read (const QString &fileName);
};

} // Internal
} // SndFile


#endif

// vim: ts=8 sw=2 sts=2 et sta noai
