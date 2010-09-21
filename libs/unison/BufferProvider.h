/*
 * BufferProvider.h
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

#ifndef UNISON_BUFFER_PROVIDER_H_
#define UNISON_BUFFER_PROVIDER_H_

#include "Buffer.h"

#include <QSharedPointer>

namespace Unison {
    
  enum PortType;
  class SharedBufferPtr;

/**
 * BufferProvider manages Buffer allocation and freeing.  All buffers used in Unison (at
 * least by Ports) should be acquired through a BufferProvider.  The goal of
 * BufferProvider is to remove buffer allocation from RT-critical code.  The secondary
 * goal is to decrease the number of heap allocations.  Implementations are free to
 * pre-allocate data, allocate on demand, defer freeing, just as long as everything is
 * sane.
 */
class BufferProvider
{
  Q_DISABLE_COPY(BufferProvider)
  public:
    BufferProvider ()
    {};

    virtual ~BufferProvider ()
    {};

    /**
     * Aquire a buffer of requested type and size.  This function is expected to succeed.
     * Calling this function may cause a heap allocation.  More thought needs to go into
     * calling acquire() from RT code.
     * @param type The type of buffer to acquire
     * @param nframes The (minimum) size of the buffer to acquire
     * @returns The newly allocated, or recycled, buffer
     */
    virtual SharedBufferPtr acquire (PortType type, nframes_t nframes) = 0;

    /**
     * "Zero" buffers are handy for unconnected input-ports.  A Shared pointer to shared
     * data is returned since a zero buffer always has the same data (all silence)
     * @returns A buffer, for read only, with all values = 0.0f
     */
    virtual SharedBufferPtr zeroAudioBuffer () const = 0;

  protected:
    /**
     * Releases the buffer, buf.  Visibility is protected since this function should only
     * be called by SharedBufferPtr when a buffer is no longer referenced; in that case,
     * the destructor of the buffer will be called.  Release implies that the buffer is
     * either returned to the system or it is returned to the "free pool".  Of course if
     * returning to the system is not RT-safe, then this operation will have to be
     * deferred.
     * @param buf The buffer to release
     */
    virtual void release (Buffer* buf) = 0;

    friend class SharedBufferPtr;
};



/**
 * A Smart-pointer to a Buffer.  Provides a reference-counted pointer to a Buffer.  This
 * allows multiple Ports to reference the same buffer without the complexity of ownership.
 * The Buffer is returned to the BufferProvider when no more references to this Buffer
 * exist.
 * @seealso BufferProvider::release()
 */
class SharedBufferPtr : public QSharedPointer<Buffer>
{
  public:
    SharedBufferPtr () :
      QSharedPointer<Buffer>()
    {}

    SharedBufferPtr (Buffer* buf) :
      QSharedPointer<Buffer>( buf, SharedBufferPtr::deleter )
    {}

  private:
    static void deleter (Buffer* buf)
    {
      if (buf) {
        buf->m_provider.release(buf);
      }
    }
};

} // Unison

#endif

// vim: tw=90 ts=8 sw=2 sts=2 et sta noai
