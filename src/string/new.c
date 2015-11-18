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
#include <string.h>



/**
 * Variant of `strlen` that treats both NUL and a
 * selected byte as the termination-byte.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str   The string.
 * @param   stop  The additional termination-byte.
 * @return        The number of bytes before, the first termination-byte.
 */
size_t strclen(const char* string, int stop)
{
  return (size_t)(strchrnul(string, stop) - string);
}

/**
 * Variant of `strclen` that only inspects the
 * beginning of a string.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str     The string.
 * @param   stop    The additional termination-byte.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of bytes before, the first termination-byte.
 *                  `maxlen` if no termination-byte was found.
 */
size_t strcnlen(const char* string, int stop, size_t maxlen)
{
  const char* end = strnchr(string, stop, maxlen);
  return end ? (size_t)(end - string) : maxlen;
}

/**
 * Variant of `strlen` that treats both NUL and a
 * selected string as the termination-mark.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str   The string.
 * @param   stop  The additional termination-mark.
 * @return        The number of bytes before, the first termination-mark.
 */
size_t strstrlen(const char* string, const char* stop)
{
  const char* end = strstr(string, stop);
  return end ? (size_t)(end - string) : strlen(string);
}

/**
 * Variant of `strstrlen` that only inspects the
 * beginning of a string.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str     The string.
 * @param   stop    The additional termination-mark.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of bytes before, the first termination-mark.
 *                  `maxlen` if no termination-byte was found.
 */
size_t strstrnlen(const char* string, const char* stop, size_t maxlen)
{
  const char* end = strnstr(string, stop, maxlen);
  return end ? (size_t)(end - string) : maxlen;
}

char* (strnchr)(const char* string, int c, size_t maxlen) /* slibc: completeness */
{
  for (;;)
    if (*string == c)
      return string;
    else if (!*string++ || !maxlen--)
      return NULL;
}

char* (strnchrnul)(const char* string, int c, size_t maxlen) /* slibc+gnu: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || !maxlen--)
      return string;
}

char* (memcchr)(const char* segment, int c, int stop, size_t size) /* slibc: completeness */
{
  char* s = segment;
  for (;;)
    if (*s == c)
      return s;
    else if ((*s++ == stop) || !size--)
      return NULL;
}

char* (strcchr)(const char* string, int c, int stop) /* slibc: completeness */
{
  for (;;)
    if (*string == c)
      return string;
    else if (!*string || (*string++ == stop))
      return NULL;
}

char* (strcnchr)(const char* string, int c, int stop, size_t maxlen) /* slibc: completeness */
{
  for (;;)
    if (*string == c)
      return string;
    else if (!*string || (*string++ == stop) || !maxlen--)
      return NULL;
}

char* (strcchrnul)(const char* string, int c, int stop) /* slibc+gnu: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop))
      return string;
}

char* (strcnchrnul)(const char* string, int c, int stop, size_t maxlen) /* slibc+gnu: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop) || !maxlen--)
      return string;
}

char* (strnrchr)(const char* string, int c, size_t maxlen) /* slibc: completeness */
{
  char* r = NULL;
  while (maxlen--)
    if (*string == c)
      r = string;
    else if (!*string++)
      return c ? r : (string - 1);
}

void* (memcrchr)(const void* segment, int c, int stop, size_t size) /* slibc: completeness */
{
  char* r = NULL;
  for (;; size--)
    if (*segment == c)
      r = segment;
    else if ((*segment == stop) || !size)
      return r;
}

char* (strcrchr)(const char* string, int c, int stop) /* slibc: completeness */
{
  char* r = NULL;
  for (;;)
    if (*string == c)
      r = string;
    else if (!*string++)
      return c ? r : (string - 1);
    else if (*string == stop)
      return r;
}

char* (strcnrchr)(const char* string, int c, int stop, size_t maxlen) /* slibc: completeness */
{
  char* r = NULL;
  while (maxlen--)
    if (*string == c)
      r = string;
    else if (!*string++)
      return c ? r : (string - 1);
}

void* (rawmemrchr)(const void* segment, int c, size_t size) /* slibc+gnu: completeness */
{
  char* s = segment;
  for (;;)
    if (s[--size] == c)
      return s + size;
}

void* (rawmemcasemem)(const void* haystack, const void* needle, size_t needle_length) /* slibc */
{
  return (memcasemem)(haystack, SIZE_MAX, needle, needle_length);
}

void* (rawmemmem)(const void* haystack, const void* needle, size_t needle_length) /* slibc */
{
  return (memmem)(haystack, SIZE_MAX, needle, needle_length);
}

void* (memccasemem)(const void* haystack, size_t haystack_length, const void* needle, size_t needle_length, int stop) /* slibc: completeness */
{
  const void* p = memchr(haystack, stop, haystack_length);
  return (memcasemem)(haystack, p ? (size_t)(p - haystack) : haystack_length, needle, needle_length);
}

void* (memcmem)(const void* haystack, size_t haystack_length, const void* needle, size_t needle_length, int stop) /* slibc: completeness */
{
  const void* p = memchr(haystack, stop, haystack_length);
  return (memmem)(haystack, p ? (size_t)(p - haystack) : haystack_length, needle, needle_length);
}

char* (strccasestr)(const char* haystack, const char* needle, int stop) /* slibc: completeness */
{
  return (memcasemem)(haystack, strclen(haystack, stop), needle, strlen(needle));
}

char* (strcstr)(const char* haystack, const char* needle, int stop) /* slibc: completeness */
{
  return (memmem)(haystack, strclen(haystack, stop), needle, strlen(needle));
}

char* (strcncasestr)(const char* haystack, const char* needle, int stop, size_t maxlen) /* slibc: completeness */
{
  return (memcasemem)(haystack, strcnlen(haystack, stop, maxlen), needle, strlen(needle));
}

char* (strcnstr)(const char* haystack, const char* needle, int stop, size_t maxlen) /* slibc: completeness */
{
  return (memmem)(haystack, strcnlen(haystack, stop, maxlen), needle, strlen(needle));
}

char* (strpcbrk)(const char* string, const char* skipset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (set[(size_t)c])
      break;
  return c ? (s - 1) : NULL;
}

char* (strpbrknul)(const char* string, const char* stopset) /* slibc */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (!set[(size_t)c])
      break;
  return s - 1;
}

char* (strpcbrknul)(const char* string, const char* skipset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (set[(size_t)c])
      break;
  return s - 1;
}

char* (strnpbrk)(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (!set[(size_t)c])
      break;
  return c ? (s - 1) : NULL;
}

char* (strnpcbrk)(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (set[(size_t)c])
      break;
  return c ? (s - 1) : NULL;
}

char* (strnpbrknul)(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (!set[(size_t)c])
      break;
  return s - 1;
}

char* (strnpcbrknul)(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (set[(size_t)c])
      break;
  return s - 1;
}

size_t strnspn(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256);
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  for (; maxlen && ((c = *s++)); maxlen--)
    if (set[(size_t)c])
      break;
  return (size_t)(s - !!maxlen - string);
}

size_t strncspn(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256);
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  for (; maxlen && ((c = *s++)); maxlen--)
    if (!set[(size_t)c])
      break;
  return (size_t)(s - !!maxlen - string);
}

char* strnsep(char** restrict string, const char* restrict delimiters,
	      size_t* restrict maxlen) /* slibc: completeness */
{
  char* r = *string;
  char* next;
  if (r == NULL)
    return NULL;
  
  next = strnpbrk(r, delimiters, *maxlen);
  if (next != NULL)
    *next++ = 0, *maxlen -= (size_t)(next - r);
  *string = next;
  
  return r;
}

char* strntok(char* restrict string, const char* restrict delimiters,
	      char** restrict state, size_t* restrict maxlen) /* slibc: completeness */
{
  char* r;
  if (string == NULL)
    *state = string;
  for (;;)
    {
      r = strnsep(state, delimiters, maxlen);
      if (r == NULL)
	return NULL;
      if (*r)
	return r;
    }
}

char* (strprbrk)(const char* string, const char* stopset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256);
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (!set[(size_t)c])
      r = s - 1;
  return r;
}

char* (strprcbrk)(const char* string, const char* skipset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (set[(size_t)c])
      r = s - 1;
  return r;
}

char* (strnprbrk)(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (!set[(size_t)c])
      r = s - 1;
  return r;
}

char* (strnprcbrk)(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (set[(size_t)c])
      r = s - 1;
  return r;
}

char* memmemmove(char* whither, const char* whence, const char* restrict str,
		 size_t strsize, size_t size) /* slibc: completeness */
{
  char* stop = (memmem)(whence, size, str, strsize);
  void* r = NULL;
  if (stop != NULL)
    size = (size_t)(stop - (const char*)whence), r = whither + size;
  memmove(whither, whence, size);
  return r;
}

char* memmemcpy(void* whither, const void* whence, const char* restrict str,
		size_t strsize, size_t size) /* slibc: completeness */
{
  char* stop = (memmem)(whence, size, str, strsize);
  void* r = NULL;
  if (stop != NULL)
    size = (size_t)(stop - (const char*)whence), r = whither + size;
  memcpy(whither, whence, size);
  return r;
}

void* (memcasestarts)(const void* string, const void* desired, size_t size) /* slibc: completeness */
{
  return (memcasecmp)(string, desired, size) ? NULL : string;
}

char* (strncasestarts)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string, desired, m) ? NULL : string;
}

void* (memcaseends)(const void* string, size_t string_size, const void* desired, size_t desired_size) /* slibc: completeness */
{
  return (memcasecmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

char* (strncaseends)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

void* (memstarts)(const void* string, const void* desired, size_t size) /* slibc */
{
  return (memcmp)(string, desired, size) ? NULL : string;
}

char* (strnstarts)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string, desired, m) ? NULL : string;
}

void* (memends)(const void* string, size_t string_size, const void* desired, size_t desired_size) /* slibc: completeness */
{
  return (memcmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

char* (strnends)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

int memccasecmp(const void* a, const void* b, size_t size, int stop) /* slibc: completeness */
{
  const signed char* s1 = a;
  const signed char* s2 = b;
  int c1, c2;
  for (; c1 = (int)*s1++, c2 = (int)*s2++, (c1 != stop) && (c2 != stop) && size; size--)
    if (c1 != c2)
      {
	c1 = isalpha(c1) ? tolower(c1) : c1;
	c2 = isalpha(c2) ? tolower(c2) : c2;
	if ((c1 -= c2))
	  return c1;
      }
  if (c1 == stop)  c1 = 0;
  if (c2 == stop)  c2 = 0;
  return size ? (c1 - c2) : 0;
}

int memccmp(const void* a, const void* b, size_t size, int stop) /* slibc: completeness */
{
  const signed char* s1 = a;
  const signed char* s2 = b;
  int c1, c2;
  for (; c1 = (int)*s1++, c2 = (int)*s2++, (c1 != stop) && (c2 != stop) && size; size--)
    if (c1 != c2)
      return c1 - c2;
  if (c1 == stop)  c1 = 0;
  if (c2 == stop)  c2 = 0;
  return size ? (c1 - c2) : 0;
}

int strccasecmp(const char* a, const char* b, int stop) /* slibc: completeness */
{
  return strcncasecmp(a, b, stop, SIZE_MAX);
}

int strccmp(const char* a, const char* b, int stop) /* slibc */
{
  size_t n = strclen(a, stop);
  size_t m = strclen(b, stop);
  return memcmp(a, b, (n < m ? n : m) + 1);
}

int strcncasecmp(const char* a, const char* b, int stop, size_t length) /* slibc: completeness */
{
  size_t n = strcnlen(a, stop, length);
  size_t m = strcnlen(b, stop, length);
  int r = memcasecmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}

int strcncmp(const char* a, const char* b, int stop, size_t length) /* slibc: completeness */
{
  size_t n = strcnlen(a, stop, length);
  size_t m = strcnlen(b, stop, length);
  int r = memcmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}

void* (memccasestarts)(const void* string, const void* desired, size_t size, int stop) /* slibc: completeness */
{
  return (memccasecmp)(string, desired, size, stop) ? NULL : string;
}

void* (memcstarts)(const void* string, const void* desired, size_t size, int stop) /* slibc: completeness */
{
  return (memccmp)(string, desired, size, stop) ? NULL : string;
}

char* (strccasestarts)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcasecmp)(string, desired, m) ? NULL : string;
}

char* (strcstarts)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcmp)(string, desired, m) ? NULL : string;
}

char* (strcncasestarts)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string, desired, m) ? NULL : string;
}

char* (strcnstarts)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string, desired, m) ? NULL : string;
}

void* (memccaseends)(const void* string, size_t string_size, const void* desired, size_t desired_size, int stop) /* slibc: completeness */
{
  void* end = memchr(string, stop, string);
  if (end != NULL)
    string_size = (size_t)(end - string);
  return (memcasecmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

void* (memcends)(const void* string, size_t string_size, const void* desired, size_t desired_size, int stop) /* slibc: completeness */
{
  void* end = wmemchr(string, stop, string);
  if (end != NULL)
    string_size = (size_t)(end - string);
  return (memcmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

char* (strccaseends)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

char* (strcends)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

char* (strcncaseends)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

char* (strcnends)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

