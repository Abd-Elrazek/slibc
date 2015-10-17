/**
 * slibc — Yet another C library
 * Copyright © 2015  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _LIBGEN_H
#define _LIBGEN_H
#include <slibc/version.h>
#include <slibc/features.h>



/* Override GNU-specific `basename` from <string.h>. */
#ifdef basename
# undef basename
#endif


/**
 * Get the basename of a filename, remove
 * trailing slashes.
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The basename, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or is empty, a statically allocationed string,
 *                    so it must not freed or edited.
 */
char* __xpg_basename(char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));
#define basename  __xpg_basename

/**
 * Get the dirname of a filename.
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The dirname, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or does no contain a non-trailing slash,
 *                    a statically allocationed string, so it
 *                    must not freed or edited.
 */
char* dirname(char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));



#endif

