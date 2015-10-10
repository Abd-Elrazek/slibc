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
#ifndef _STDLIB_H
#define _STDLIB_H
#include <slibc/version.h>
#include <slibc/features.h>


#include <malloc.h>



#define __NEED_size_t
#define __NEED_wchar_t
#define __NEED_div_t
#define __NEED_ldiv_t
#define __NEED_lldiv_t

#include <bits/types.h>


/**
 * `NULL`'s canonical header is <stddef.h>.
 */
#ifndef NULL
# define NULL  ((void*)0)
#endif


/**
 * The value a process shall exit with upon
 * success completion.
 */
#define EXIT_SUCCESS  0

/**
 * A standard value a process can exit with
 * if it terminates because of failure.
 */
#define EXIT_FAILURE  1



/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 */
div_t div(int, int)
  __GCC_ONLY(__attribute__((const)));

/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 */
ldiv_t ldiv(long, long)
  __GCC_ONLY(__attribute__((const)));

/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 */
lldiv_t lldiv(long long, long long)
  __GCC_ONLY(__attribute__((const)));


#if !defined(__PORTABLE)
/**
 * Get the absolute path of a file.
 * It will remove all redundant slashes, all "./":s,
 * and all "../":s, but not resolve symbolic links.
 * 
 * This is a slibc extension.
 * 
 * @param   file  The file.
 * @param   ref   The directory the file's specified path is
 *                relative, `NULL` for the current working directory.
 * @return        The file's absolute pathname. Will end with a slash
 *                if `file` does. (Or if `ref` does but file is empty.)
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
char* abspath(const char*, const char*)
  __GCC_ONLY(__attribute__((warn_unused_result, nonnull(1), malloc)));

/**
 * Get the relative path of a file.
 * 
 * This is a slibc extension.
 * 
 * @param   file  The file.
 * @param   ref   The file the result shall be relative to,
 *                `NULL` for the current working directory.
 *                If and only if this path ends with a slash,
 *                (or if it is `NULL`,) it will be treated as
 *                a directory in which a symbolic link, with
 *                the result as it target, can be located to
 *                point to `file`.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
char* relpath(const char*, const char*)
  __GCC_ONLY(__attribute__((warn_unused_result, nonnull(1), malloc)));
#endif


/**
 * Convert a string to a floating-point value,
 * without checking for errors.
 * 
 * Note that, the behaviour is unspecified
 * if the string contains anything else than
 * digits, either a leading '-' (hyphen)
 * or a leading plus, and at most one '.'.
 * 
 * @param   string  The string to convert.
 * @return          The number encoded by the string.
 */
double atof(const char*)
  __GCC_ONLY(__attribute__((warn_unused_result, nonnull, pure)));

/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * Note that, the behaviour is unspecified
 * if the string contains anything else than
 * digits and either a leading '-' (hyphen)
 * or a leading plus.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 */
int atoi(const char*)
  __GCC_ONLY(__attribute__((warn_unused_result, nonnull, pure)));

/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * Note that, the behaviour is unspecified
 * if the string contains anything else than
 * digits and either a leading '-' (hyphen)
 * or a leading plus.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 */
long int atol(const char*)
  __GCC_ONLY(__attribute__((warn_unused_result, nonnull, pure)));

/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * Note that, the behaviour is unspecified
 * if the string contains anything else than
 * digits and either a leading '-' (hyphen)
 * or a leading plus.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 */
long long int atoll(const char*)
  __GCC_ONLY(__attribute__((warn_unused_result, nonnull, pure)));

#if !defined(__PORTABLE)
/**
 * This function is identical to `atoll`.
 * 
 * This is a Linux libc extension.
 */
long long int atoq(const char*)
  __deprecated("'atoq' is obsolete and not portable, use 'atoll' instead.")
  __GCC_ONLY(__attribute__((warn_unused_result, nonnull, pure)));
#endif



/* TODO implement rand-functions */
#define RAND_MAX  1
int rand(void);
int rand_r(unsigned int* seed);
void srand(unsigned int seed);



/* TODO implement exit-functions */
void abort(void) __noreturn;
void _Exit(int) __noreturn;
int atexit(void (*)(void));
int on_exit(void (*)(int, void*), void*);
void exit(int) __noreturn;
int at_quick_exit (void (*) (void));
void quick_exit(int) __noreturn;



#endif

