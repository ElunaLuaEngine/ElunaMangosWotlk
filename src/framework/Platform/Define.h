/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_DEFINE_H
#define MANGOS_DEFINE_H

#include <sys/types.h>

#include <ace/Basic_Types.h>
#include <ace/Default_Constants.h>
#include <ace/OS_NS_dlfcn.h>
#include <ace/ACE_export.h>

#include "Platform/CompilerDefs.h"

#define MANGOS_LITTLEENDIAN 0
#define MANGOS_BIGENDIAN    1

#if !defined(MANGOS_ENDIAN)
#  if defined (ACE_BIG_ENDIAN)
#    define MANGOS_ENDIAN MANGOS_BIGENDIAN
#  else // ACE_BYTE_ORDER != ACE_BIG_ENDIAN
#    define MANGOS_ENDIAN MANGOS_LITTLEENDIAN
#  endif // ACE_BYTE_ORDER
#endif // MANGOS_ENDIAN

typedef ACE_SHLIB_HANDLE MANGOS_LIBRARY_HANDLE;

#define MANGOS_PATH_MAX PATH_MAX                            // ace/os_include/os_limits.h -> ace/Basic_Types.h

#if !defined(DEBUG)
#  define MANGOS_INLINE inline
#else // DEBUG
#  if !defined(MANGOS_DEBUG)
#    define MANGOS_DEBUG
#  endif // MANGOS_DEBUG
#  define MANGOS_INLINE
#endif //!DEBUG

#if COMPILER == COMPILER_GNU
#  define ATTR_NORETURN __attribute__((noreturn))
#  define ATTR_PRINTF(F,V) __attribute__ ((format (printf, F, V)))
#else // COMPILER != COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F,V)
#endif // COMPILER == COMPILER_GNU

typedef ACE_INT64 int64;
typedef ACE_INT32 int32;
typedef ACE_INT16 int16;
typedef ACE_INT8 int8;
typedef ACE_UINT64 uint64;
typedef ACE_UINT32 uint32;
typedef ACE_UINT16 uint16;
typedef ACE_UINT8 uint8;

#if COMPILER != COMPILER_MICROSOFT
typedef uint16      WORD;
typedef uint32      DWORD;
#endif // COMPILER

#define CONCAT(x, y) CONCAT1(x, y)
#define CONCAT1(x, y) x##y
#define STATIC_ASSERT_WORKAROUND(expr, msg) typedef char CONCAT(static_assert_failed_at_line_, __LINE__) [(expr) ? 1 : -1]

#if COMPILER == COMPILER_GNU
#  if !defined(__GXX_EXPERIMENTAL_CXX0X__) || (__GNUC__ < 4) || (__GNUC__ == 4) && (__GNUC_MINOR__ < 7)
#    define override
#    define static_assert(a, b) STATIC_ASSERT_WORKAROUND(a, b)
#  endif
#elif COMPILER == COMPILER_MICROSOFT
#  if _MSC_VER < 1600
#    define static_assert(a, b) STATIC_ASSERT_WORKAROUND(a, b)
#  endif
#endif

typedef uint64 OBJECT_HANDLE;

#endif // MANGOS_DEFINE_H
