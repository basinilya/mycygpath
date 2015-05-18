/* strfuncs.cc: string functions

   Copyright 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2007, 2008, 2009, 2010, 2011, 2012, 2013 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#include "mycygpath.h"

/* Transform characters invalid for Windows filenames to the Unicode private
   use area in the U+f0XX range.  The affected characters are all control
   chars 1 <= c <= 31, as well as the characters " * : < > ? |.  The backslash
   is affected as well, but we can't transform it as long as we accept Win32
   paths as input. */
static const WCHAR tfx_chars[] = {
	    0, 0xf000 |   1, 0xf000 |   2, 0xf000 |   3,
 0xf000 |   4, 0xf000 |   5, 0xf000 |   6, 0xf000 |   7,
 0xf000 |   8, 0xf000 |   9, 0xf000 |  10, 0xf000 |  11,
 0xf000 |  12, 0xf000 |  13, 0xf000 |  14, 0xf000 |  15,
 0xf000 |  16, 0xf000 |  17, 0xf000 |  18, 0xf000 |  19,
 0xf000 |  20, 0xf000 |  21, 0xf000 |  22, 0xf000 |  23,
 0xf000 |  24, 0xf000 |  25, 0xf000 |  26, 0xf000 |  27,
 0xf000 |  28, 0xf000 |  29, 0xf000 |  30, 0xf000 |  31,
	  ' ',          '!', 0xf000 | '"',          '#',
	  '$',          '%',          '&',           39,
	  '(',          ')', 0xf000 | '*',          '+',
	  ',',          '-',          '.',          '/', /* < keep forward slash */
	  '0',          '1',          '2',          '3',
	  '4',          '5',          '6',          '7',
	  '8',          '9', 0xf000 | ':',          ';',
 0xf000 | '<',          '=', 0xf000 | '>', 0xf000 | '?',
	  '@',          'A',          'B',          'C',
	  'D',          'E',          'F',          'G',
	  'H',          'I',          'J',          'K',
	  'L',          'M',          'N',          'O',
	  'P',          'Q',          'R',          'S',
	  'T',          'U',          'V',          'W',
	  'X',          'Y',          'Z',          '[',
	  '\\',          ']',          '^',          '_',
	  '`',          'a',          'b',          'c',
	  'd',          'e',          'f',          'g',
	  'h',          'i',          'j',          'k',
	  'l',          'm',          'n',          'o',
	  'p',          'q',          'r',          's',
	  't',          'u',          'v',          'w',
	  'x',          'y',          'z',          '{',
 0xf000 | '|',          '}',          '~',          127
};

void
_transform_chars (PWCHAR path, PWCHAR path_end)
{
  for (; path <= path_end; ++path)
    if (*path < 128)
      *path = tfx_chars[*path];
}
