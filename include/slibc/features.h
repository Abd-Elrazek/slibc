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
#ifndef _SLIBC_FEATURES_H
#define _SLIBC_FEATURES_H


/* These definitions are only to be used in slibc header-files. */


/**
 * Macro that is defined if portability shall be ensured.
 */
#if defined(_PORTABLE_SOURCE) || defined(_LIBRARY_HEADER)
# define __PORTABLE
#endif


/**
 * Is C11, or newer, used?
 */
#if __STDC_VERSION__ >= 201112L || defined(_ISOC11_SOURCE)
# define __C11__
#endif

/**
 * Is C99, or newer, used?
 */
#if __STDC_VERSION__ >= 199901L || defined(_ISOC99_SOURCE)
# define __C99__
#endif

/**
 * Is C90, or newer, used?
 */
#if defined(__STDC_VERSION__) || defined(__STDC__)
# define __C90__
#endif



/**
 * _POSIX_SOURCE is implied if (_POSIX_C_SOURCE >= 1L).
 */
#if !defined(_POSIX_SOURCE) && defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 1L)
# define _POSIX_SOURCE 1
#endif
#if (!defined(_POSIX_C_SOURCE) || (_POSIX_C_SOURCE <= 0)) && !defined(_POSIX_SOURCE)
# define _POSIX_C_SOURCE  1L
#endif

/**
 * _BSD_SOURCE || _SVID_SOURCE implies _POSIX_C_SOURCE = 2.
 */
#if defined(_BSD_SOURCE) || defined(_SVID_SOURCE)
# if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE < 1L)
#  undef _POSIX_C_SOURCE
# endif
# if !defined(_POSIX_C_SOURCE)
#  define _POSIX_C_SOURCE  2
# endif
#endif

/**
 * _SVID_SOURCE implies _XOPEN_SOURCE
 */
#if defined(_SVID_SOURCE) && !defined(_XOPEN_SOURCE)
# define _XOPEN_SOURCE  1
#endif

/**
 * _BSD_COMPATIBLE_SOURCE requires _BSD_SOURCE.
 */
#if defined(_BSD_COMPATIBLE_SOURCE) && !defined(_BSD_SOURCE)
# if !defined(_SLIBC_SUPPRESS_WARNINGS)
#  warning "_BSD_COMPATIBLE_SOURCE is defined, but _BSD_SOURCE is undefined."
# endif
#endif

/**
 * _BSD_COMPATIBLE_SOURCE and _POSIX_COMPATIBLE_SOURCE
 * are incompatible.
 */
#if defined(_BSD_COMPATIBLE_SOURCE) && defined(_POSIX_COMPATIBLE_SOURCE)
# if !defined(_SLIBC_SUPPRESS_WARNINGS)
#  warning "You should not define both _BSD_COMPATIBLE_SOURCE and _POSIX_COMPATIBLE_SOURCE."
# endif
#endif


/**
 * Feature-test macros that also change that
 * `_PORTABLE_SOURCE` and `_LIBRARY_HEADER`
 * is not defined.
 */
#if !defined(__PORTABLE)
# if defined(_GNU_SOURCE)
#  define __GNU_SOURCE  _GNU_SOURCE
# endif
# if defined(_SLIBC_SOURCE)
#  define __SLIBC_SOURCE  _SLIBC_SOURCE
# endif
# if defined(_BSD_SOURCE)
#  define __BSD_SOURCE  _BSD_SOURCE
# endif
# if defined(_XOPEN_SOURCE)
#  define __XOPEN_SOURCE  _XOPEN_SOURCE
# endif
# if defined(_ISOC11_SOURCE)
#  define __ISOC11_SOURCE  _ISOC11_SOURCE
# endif
#endif
#if defined(_POSIX_SOURCE)
# define __POSIX_SOURCE  _POSIX_SOURCE
#endif
#if defined(_POSIX_C_SOURCE)
# define __POSIX_C_SOURCE  _POSIX_C_SOURCE
#endif



/**
 * Macro used to exclude code unless GCC is used.
 */
#if defined(__GNUC__)
# define __GCC_ONLY(...)   __VA_ARGS__
#else
# define __GCC_ONLY(...)   /* ignore */
#endif


/**
 * Specifies that a function never returns, that is,
 * the process exits before the function returns.
 */
#if !defined(__C11__) && defined(__GNUC__)
# define __noreturn  __attribute__((noreturn))
#elif defined(__C11__)
# define __noreturn  _Noreturn
#else
# define __noreturn  /* ignore */
#endif


/**
 * Macro used to exclude code unless `_SLIBC_SOURCE` is set.
 */
#if defined(_SLIBC_SOURCE)
# define __SLIBC_ONLY(...)  __VA_ARGS__
#else
# define __SLIBC_ONLY(...)  /* ignore */
#endif


/**
 * Mark a function, variable or type as deprecated,
 * with a message that tells the user why the the
 * function is deprecated, or functions to use instead.
 */
#if !defined(_SLIBC_SUPPRESS_WARNINGS)
# define __deprecated(msg)  __GCC_ONLY(__attribute__((deprecated(msg))))
#else
# define __deprecated(msg)  /* ignore */
#endif


/**
 * Warn if a function, variable or type is used.
 */
#if !defined(_SLIBC_SUPPRESS_WARNINGS)
# define __warning(msg)        __GCC_ONLY(__attribute__((warning(msg))))
# define __slibc_warning(msg)  __SLIBC_ONLY(__warning(msg))
#else
# define __warning(msg)        /* ignore */
# define __slibc_warning(msg)  /* ignore */
#endif


/**
 * Functions that have a BSD-specification that is conficting
 * with the POSIX-specification shall have this attribute.
 */
#if defined(_BSD_SOURCE) && !defined(_POSIX_COMPATIBLE_SOURCE) && !defined(_BSD_COMPATIBLE_SOURCE)
# define __bsd_posix_conflict  \
  __warning("The BSD-version of this function is incompatible with the POSIX-version.")
#else
# define __bsd_posix_conflict  /* ignore*/
#endif


/**
 * Format for the `format` GCC function attribute,
 * for `*printf` functions.
 */
#define slibc_printf  printf /* TODO write GCC extension */

/**
 * Format for the `format` GCC function attribute,
 * for `*scanf` functions.
 */
#define slibc_scanf  scanf /* TODO write GCC extension */



#endif

