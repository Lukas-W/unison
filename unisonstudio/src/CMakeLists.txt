#
# CMakeLists.txt - The sources CMake file
#
# Copyright (c) 2010 Paul Giblock <pgib/at/users.sourceforge.net>
#
# This file is part of Unison - http://unison.sourceforge.net/
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public
# License along with this program (see COPYING); if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
#

#file(GLOB UNISONSTUDIO_SRCS *.cpp)
set(UNISONSTUDIO_SRCS
    main.cpp
)

include_directories(
    ${COMMON_LIBS_INCLUDE_DIR}
    #${UNISON_INCLUDE_DIR}
    #${PRG_INCLUDE_DIR}
)

add_executable(unisonstudio
    ${UNISONSTUDIO_SRCS}
)

target_link_libraries(unisonstudio
    extensionsystem
)

install(TARGETS unisonstudio RUNTIME
        DESTINATION bin/)

# vim: tw=90 ts=8 sw=2 sts=2 et sta noai
