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
#ifndef _STRING_H
#define _STRING_H
#include <slibc/version.h>


#include <slibc/features.h>



#define __NEED_size_t
#define __NEED_locale_t /* TODO not defined */

#include <bits/types.h>



/**
 * Return a textual representation of an error code.
 * This error code must from `errno`.
 * 
 * This implementation of `strerror` cannot fail. however
 * POSIX specifies that it can fail, any may only set `errno`
 * if it does fail. You should therefore, set `errno` to
 * zero before calling this function, and inspect `errno`
 * when it returns, as there is no reserved return value
 * that indicates and error.
 * 
 * The returned value must not be modified or freed.
 * 
 * As a slibc-specific modification, this function is MT-Safe.
 * 
 * @param   errnum  The error code.
 * @return          A description of the error.
 */
char* strerror(int)
  __GCC_ONLY(__attribute__((returns_nonnull)));

/**
 * Return a textual representation of an error code.
 * This error code must from `errno`.
 * 
 * POSIX specifies `errno` may only be set on failure,
 * and reserves no return value to indicate such.
 * You should therefore, set `errno` to zero before calling
 * this function, and inspect `errno` when it returns.
 * 
 * The returned value must not be modified or freed.
 * 
 * As a slibc-specific modification, this function is MT-Safe.
 * 
 * @param   errnum  The error code.
 * @param   locale  The locale, must be a valid locale and not
 *                  `LC_GLOBAL_LOCALE`, lest the behaviour is undefined.
 * @return          A description of the error.
 */
char* strerror_l(int, locale_t);


#if !defined(_PORTABLE_SOURCE) && !defined(_SLIBC_SOURCE)
/**
 * Reenterant variant of `stderror`.
 * 
 * This is an XSI-compliant extension. However the name
 * is not part of the XSI specification, `strerror_r`
 * should be used. It is defined to this function if
 * `(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE`.
 * However it is not defined if _SLIBC_SOURCE is defined.
 * 
 * @param   errnum  The error code.
 * @param   buf     Buffer where the description shall be stored.
 * @param   buflen  The allocation size of `buf`.
 * @return          Zero on success, value for `errno` on error
 * 
 * @throws  ERANGE  `buf` was too small to store the description.
 */
int __xsi_strerror_r(int, char*, size_t); /* XSI-compliant strerror_r */

/**
 * Reenterant variant of `stderror`.
 * 
 * This is a GNU-specific extension. However the name
 * is not part of the GNU specification, `strerror_r` should
 * be used. It is defined to this function unless
 * `(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE`.
 * However it is not defined if _SLIBC_SOURCE is defined.
 * 
 * @param   errnum  The error code.
 * @param   buf     Buffer where the description shall be stored.
 * @param   buflen  The allocation size of `buf`.
 * @return          `buf` on success, `NULL` on error. On error, `errno`
 *                  is set to indicate the error.
 * 
 * @throws  ERANGE  `buf` was too small to store the description.
 */
char* __gnu_strerror_r(int, char*, size_t); /* GNU-specific strerror_r */

# if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !defined(_GNU_SOURCE)
#  define strerror_r  __xsi_strerror_r
# else
#  define strerror_r  __gnu_strerror_r
# endif
#endif



#endif

