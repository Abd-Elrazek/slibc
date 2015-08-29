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
#ifndef _STDNORETURN_H
#define _STDNORETURN_H
#include <slibc/version.h>


#include <slibc/features.h>



/**
 * Specifies that a function never returns, that is,
 * the process exits before the function returns.
 */
#if !defined(__C11__) && defined(__GNUC__)
# define _Noreturn  __attribute__((noreturn))
#endif
#define noreturn  _Noreturn



#endif

