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
#include <wchar.h>


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Find the last occurrence of a wide character in a string.
 * 
 * For improved performace, use `wmemrchr` instead of
 * this function if you already know the length of the
 * string.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @return          Pointer to the last occurrence of `c`,
 *                  `NULL` if none were found.
 */
wchar_t* (wcsrchr)(const wchar_t* string, wchar_t c)
{
  wchar_t* r = NULL;
  for (;;)
    if (*string == c)
      r = string;
    else if (!*string++)
      return c ? r : (string - 1);
}
