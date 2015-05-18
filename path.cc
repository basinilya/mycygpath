/* path.cc: path support.

     Copyright 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005,
     2006, 2007, 2008, 2009, 2010, 2011, 2012, 2013, 2014, 2015 Red Hat, Inc.

  This file is part of Cygwin.

  This software is a copyrighted work licensed under the terms of the
  Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
  details. */

#include "mycygpath.h"

PUNICODE_STRING
mycygpath(UNICODE_STRING *pupath, int dos) /* was "get_nt_native_path" */
{
  UNICODE_STRING &upath = *pupath;
  transform_chars (&upath, 0);
  if (dos)
    {
      /* Unfortunately we can't just use transform_chars with the tfx_rev_chars
	 table since only leading and trailing spaces and dots are affected.
	 So we step to every backslash and fix surrounding dots and spaces.
	 That makes these broken filesystems a bit slower, but, hey. */
      PWCHAR cp = upath.Buffer + 0;
      PWCHAR cend = upath.Buffer + upath.Length / sizeof (WCHAR);
	bool justdots = true;
	while ((justdots &= (*cp == '.')), ++cp < cend)
		if (*cp == L'/') /* < forward slash kept */
		{
			if (!justdots) {
				PWCHAR ccp = cp - 1;
				while (*ccp == L'.' || *ccp == L' ')
					*ccp-- |= 0xf000;
				while (cp[1] == L' ')
					*++cp |= 0xf000;
				justdots = true;
			}
			++cp;
		}
	if (!justdots) while (*--cp == L'.' || *cp == L' ')
		*cp |= 0xf000;

    }
  return &upath;
}
