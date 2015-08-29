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
#ifndef _STDALIGN_H
#define _STDALIGN_H
#include <slibc/version.h>



/**
 * Specify the alignment of a variable.
 * 
 * @param  type  The type whose alignment shall be used.
 */
#if __STDC_VERSION__ < 201112L && defined(__GNUC__)
# define _Alignas(type)  __attribute__((__aligned__(type)))
#endif
#define alignas(type)  _Alignas(type)


/**
 * Get the alignment of a type.
 * 
 * @param   type  The type.
 * @return        The alignment of the type.
 */
#if __STDC_VERSION__ < 201112L && defined(__GNUC__)
# define _Alignof(type)  __alignof__(type)
#endif
#define alignof(type)  _Alignof(type)



#endif

