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
#ifndef _STDIO_H
#define _STDIO_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_fpos_t /* TODO not implemented */
#define __NEED_off_t
#define __NEED_size_t
#define __NEED_ssize_t
#define __NEED_wchar_t
#define __NEED_va_list
#if __STDC_VERSION__ >= 201112L
# define __NEED_max_align_t
#endif
#define FILE void /* TODO temporary */

#include <bits/types.h>



/* TODO implement I/O */
int fflush(FILE*);
#define stdin ((void*)1) /* TODO temporary */
#define stdout ((void*)2) /* TODO temporary */
#define stderr ((void*)3) /* TODO temporary */


/**
 * This function is identical to `fprintf` with
 * `stdout` as the first argument.
 * 
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 */
int printf(const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1), format(slibc_printf, 1, 2))));

/**
 * Print a formatted string to a stream.
 * 
 * TODO list format rules for fprintf
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 */
int fprintf(FILE* restrict, const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1, 2), format(slibc_printf, 2, 3))));

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `fprintf`,
 * except it does not lock the stream.
 * 
 * This is a slibc extension.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 */
int fprintf_unlocked(FILE* restrict, const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1, 2), format(slibc_printf, 2, 3))));
#endif

/**
 * This function is identical to `fprintf`,
 * except it is limited to file descriptor-backed
 * streams, and uses the file descriptor as the
 * first argument rather than the stream.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 */
int dprintf(int, const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(2), format(slibc_printf, 2, 3))));

/**
 * This function is identical to `fprintf`,
 * it prints to a buffer rather than a stream.
 * 
 * This is identical to `snprintf` with
 * `SIZE_MAX` as the second argument.
 * 
 * @param   buffer  The output buffer.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 */
int sprintf(char* restrict, const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1, 2), format(slibc_printf, 2, 3))));

/**
 * This function is identical to `sprintf`,
 * expect it truncates the output.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 */
int snprintf(char* restrict, size_t, const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(3), format(slibc_printf, 3, 4))));

#if defined(_GNU_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `sprintf`,
 * except it allocates a sufficiently large
 * buffer.
 * 
 * This is a GNU extension.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int asprintf(char** restrict, const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1, 2), format(slibc_printf, 2, 3), warn_unused_result)));
#endif

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `asprintf`,
 * except it can reuse allocated buffers.
 * 
 * This is a slibc extension.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int bprintf(char** restrict, size_t* restrict, size_t, int, const char* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1, 2, 5), format(slibc_printf, 5, 6), warn_unused_result)));
#endif


/**
 * This function is identical to `printf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 */
int vprintf(const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(1))));

/**
 * This function is identical to `fprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 */
int vfprintf(FILE* restrict, const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `fprintf_unlocked`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 */
int vfprintf_unlocked(FILE* restrict, const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));
#endif

/**
 * This function is identical to `vdprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `write`.
 */
int vdprintf(int, const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(2))));

/**
 * This function is identical to `sprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   buffer  The output buffer.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 */
int vsprintf(char* restrict, const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));

/**
 * This function is identical to `snprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 */
int vsnprintf(char* restrict, size_t, const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(1, 3))));

#if defined(_GNU_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `asprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a GNU extension.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int vasprintf(char** restrict, const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(1, 2), warn_unused_result)));
#endif

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `bprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int vbprintf(char** restrict, size_t* restrict, size_t, int, const char* restrict, va_list)
  __GCC_ONLY(__attribute__((nonnull(1, 2, 5), warn_unused_result)));
#endif


#if !defined(__PORTABLE) /* wchar_t is not portable. */
/**
 * This function is identical to `printf` except
 * it uses wide characters.
 * 
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 */
int wprintf(const wchar_t* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1))));

/**
 * This function is identical to `fprintf` except
 * it uses wide characters.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `fwrite`.
 */
int fwprintf(FILE* restrict, const wchar_t* restrict, ...)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));

# if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `fprintf_unlocked` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 */
int fwprintf_unlocked(FILE* restrict, const wchar_t* restrict, ...)
 __GCC_ONLY(__attribute__((nonnull(1, 2))));

/**
 * This function is identical to `dprintf` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 */
int dwprintf(int, const wchar_t* restrict, ...)
 __GCC_ONLY(__attribute__((nonnull(2))));
# endif

/**
 * This function is identical to `snprintf`
 * (not `sprintf`) except it uses wide characters.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 */
int swprintf(wchar_t* restrict, size_t, const wchar_t* restrict, ...)
 __GCC_ONLY(__attribute__((nonnull(3))));

# if defined(_GNU_SOURCE) && defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `aswprintf` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * This is only available if GNU extensions are enabled.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int aswprintf(wchar_t** restrict, const wchar_t* restrict, ...)
 __GCC_ONLY(__attribute__((nonnull(1, 2), warn_unused_result)));
# endif

# if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `bprintf` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size,
 *                  in `wchar_t`.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int bwprintf(wchar_t** restrict, size_t* restrict, size_t, int, const wchar_t* restrict, ...)
 __GCC_ONLY(__attribute__((nonnull(1, 2, 5), warn_unused_result)));
# endif


/**
 * This function is identical to `wprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 */
int vwprintf(const wchar_t* restrict, va_list)
 __GCC_ONLY(__attribute__((nonnull(1))));

/**
 * This function is identical to `fwprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 */
int vfwprintf(FILE* restrict, const wchar_t* restrict, va_list)
 __GCC_ONLY(__attribute__((nonnull(1, 2))));

# if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `fwprintf_unlocked`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 */
int vfwprintf_unlocked(FILE* restrict, const wchar_t* restrict, va_list)
 __GCC_ONLY(__attribute__((nonnull(1, 2))));

/**
 * This function is identical to `vdprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 */
int vdwprintf(int, const wchar_t* restrict, va_list)
 __GCC_ONLY(__attribute__((nonnull(2))));
# endif

/**
 * This function is identical to `swprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 */
int vswprintf(wchar_t* restrict, size_t, const wchar_t* restrict, va_list)
 __GCC_ONLY(__attribute__((nonnull(3))));

# if defined(_GNU_SOURCE) && defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `aswprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * This is only available if GNU extensions are enabled.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int vaswprintf(wchar_t** restrict, const wchar_t* restrict, va_list)
 __GCC_ONLY(__attribute__((nonnull(1, 2), warn_unused_result)));
# endif

# if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * This function is identical to `bwprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size,
 *                  in `wchar_t`.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
int vbwprintf(wchar_t** restrict, size_t* restrict, size_t, int, const wchar_t* restrict, va_list)
 __GCC_ONLY(__attribute__((nonnull(1, 2, 5), warn_unused_result)));
# endif
#endif



#endif

