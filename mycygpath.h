#ifndef _MYCYGPATH_H
#define _MYCYGPATH_H

#ifdef __cplusplus
extern "C" {
#endif

typedef wchar_t WCHAR, *PWCHAR, *PWSTR;
typedef unsigned short USHORT;

typedef struct _LSA_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} LSA_UNICODE_STRING, *PLSA_UNICODE_STRING, UNICODE_STRING, *PUNICODE_STRING;

extern void _transform_chars(PWCHAR, PWCHAR);
extern inline void
transform_chars(PUNICODE_STRING upath, USHORT start_idx)
{
	_transform_chars(upath->Buffer + start_idx,
		upath->Buffer + upath->Length / sizeof (WCHAR)-1);
}

PUNICODE_STRING
mycygpath(UNICODE_STRING *upath, int dos);

#ifdef __cplusplus
}
#endif

#endif
