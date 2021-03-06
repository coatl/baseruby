/**********************************************************************

  regerror.c -  Oniguruma (regular expression library)

  Copyright (C) 2002-2005  K.Kosako (sndgk393 AT ybb DOT ne DOT jp)

**********************************************************************/
#include "regint.h"
#include <stdio.h> /* for vsnprintf() */

#ifdef HAVE_STDARG_PROTOTYPES
#include <stdarg.h>
#define va_init_list(a,b) va_start(a,b)
#else
#include <varargs.h>
#define va_init_list(a,b) va_start(a)
#endif

extern char*
onig_error_code_to_format(int code)
{
  char *p;

  if (code >= 0) return (char* )0;

  switch (code) {
  case ONIG_MISMATCH:
    p = "mismatch"; break;
  case ONIG_NO_SUPPORT_CONFIG:
    p = "no support in this configuration"; break;
  case ONIGERR_MEMORY:
    p = "fail to memory allocation"; break;
  case ONIGERR_MATCH_STACK_LIMIT_OVER:
    p = "match-stack limit over"; break;
  case ONIGERR_TYPE_BUG:
    p = "undefined type (bug)"; break;
  case ONIGERR_PARSER_BUG:
    p = "internal parser error (bug)"; break;
  case ONIGERR_STACK_BUG:
    p = "stack error (bug)"; break;
  case ONIGERR_UNDEFINED_BYTECODE:
    p = "undefined bytecode (bug)"; break;
  case ONIGERR_UNEXPECTED_BYTECODE:
    p = "unexpected bytecode (bug)"; break;
  case ONIGERR_DEFAULT_ENCODING_IS_NOT_SETTED:
    p = "default multibyte-encoding is not setted"; break;
  case ONIGERR_SPECIFIED_ENCODING_CANT_CONVERT_TO_WIDE_CHAR:
    p = "can't convert to wide-char on specified multibyte-encoding"; break;
  case ONIGERR_INVALID_ARGUMENT:
    p = "invalid argument"; break;
  case ONIGERR_END_PATTERN_AT_LEFT_BRACE:
    p = "end pattern at left brace"; break;
  case ONIGERR_END_PATTERN_AT_LEFT_BRACKET:
    p = "end pattern at left bracket"; break;
  case ONIGERR_EMPTY_CHAR_CLASS:
    p = "empty char-class"; break;
  case ONIGERR_PREMATURE_END_OF_CHAR_CLASS:
    p = "premature end of char-class"; break;
  case ONIGERR_END_PATTERN_AT_BACKSLASH:
    p = "end pattern at backslash"; break;
  case ONIGERR_END_PATTERN_AT_META:
    p = "end pattern at meta"; break;
  case ONIGERR_END_PATTERN_AT_CONTROL:
    p = "end pattern at control"; break;
  case ONIGERR_META_CODE_SYNTAX:
    p = "illegal meta-code syntax"; break;
  case ONIGERR_CONTROL_CODE_SYNTAX:
    p = "illegal control-code syntax"; break;
  case ONIGERR_CHAR_CLASS_VALUE_AT_END_OF_RANGE:
    p = "char-class value at end of range"; break;
  case ONIGERR_CHAR_CLASS_VALUE_AT_START_OF_RANGE:
    p = "char-class value at start of range"; break;
  case ONIGERR_UNMATCHED_RANGE_SPECIFIER_IN_CHAR_CLASS:
    p = "unmatched range specifier in char-class"; break;
  case ONIGERR_TARGET_OF_REPEAT_OPERATOR_NOT_SPECIFIED:
    p = "target of repeat operator is not specified"; break;
  case ONIGERR_TARGET_OF_REPEAT_OPERATOR_INVALID:
    p = "target of repeat operator is invalid"; break;
  case ONIGERR_NESTED_REPEAT_OPERATOR:
    p = "nested repeat operator"; break;
  case ONIGERR_UNMATCHED_CLOSE_PARENTHESIS:
    p = "unmatched close parenthesis"; break;
  case ONIGERR_END_PATTERN_WITH_UNMATCHED_PARENTHESIS:
    p = "end pattern with unmatched parenthesis"; break;
  case ONIGERR_END_PATTERN_IN_GROUP:
    p = "end pattern in group"; break;
  case ONIGERR_UNDEFINED_GROUP_OPTION:
    p = "undefined group option"; break;
  case ONIGERR_INVALID_POSIX_BRACKET_TYPE:
    p = "invalid POSIX bracket type"; break;
  case ONIGERR_INVALID_LOOK_BEHIND_PATTERN:
    p = "invalid pattern in look-behind"; break;
  case ONIGERR_INVALID_REPEAT_RANGE_PATTERN:
    p = "invalid repeat range {lower,upper}"; break;
  case ONIGERR_TOO_BIG_NUMBER:
    p = "too big number"; break;
  case ONIGERR_TOO_BIG_NUMBER_FOR_REPEAT_RANGE:
    p = "too big number for repeat range"; break;
  case ONIGERR_UPPER_SMALLER_THAN_LOWER_IN_REPEAT_RANGE:
    p = "upper is smaller than lower in repeat range"; break;
  case ONIGERR_EMPTY_RANGE_IN_CHAR_CLASS:
    p = "empty range in char class"; break;
  case ONIGERR_MISMATCH_CODE_LENGTH_IN_CLASS_RANGE:
    p = "mismatch multibyte code length in char-class range"; break;
  case ONIGERR_TOO_MANY_MULTI_BYTE_RANGES:
    p = "too many multibyte code ranges are specified"; break;
  case ONIGERR_TOO_SHORT_MULTI_BYTE_STRING:
    p = "too short multibyte code string"; break;
  case ONIGERR_TOO_BIG_BACKREF_NUMBER:
    p = "too big backref number"; break;
  case ONIGERR_INVALID_BACKREF:
#ifdef USE_NAMED_GROUP
    p = "invalid backref number/name"; break;
#else
    p = "invalid backref number"; break;
#endif
  case ONIGERR_NUMBERED_BACKREF_OR_CALL_NOT_ALLOWED:
    p = "numbered backref/call is not allowed. (use name)"; break;
  case ONIGERR_TOO_BIG_WIDE_CHAR_VALUE:
    p = "too big wide-char value"; break;
  case ONIGERR_TOO_LONG_WIDE_CHAR_VALUE:
    p = "too long wide-char value"; break;
  case ONIGERR_INVALID_WIDE_CHAR_VALUE:
    p = "invalid wide-char value"; break;
  case ONIGERR_EMPTY_GROUP_NAME:
    p = "group name is empty"; break;
  case ONIGERR_INVALID_GROUP_NAME:
    p = "invalid group name <%n>"; break;
  case ONIGERR_INVALID_CHAR_IN_GROUP_NAME:
#ifdef USE_NAMED_GROUP
    p = "invalid char in group name <%n>"; break;
#else
    p = "invalid char in group number <%n>"; break;
#endif
  case ONIGERR_UNDEFINED_NAME_REFERENCE:
    p = "undefined name <%n> reference"; break;
  case ONIGERR_UNDEFINED_GROUP_REFERENCE:
    p = "undefined group <%n> reference"; break;
  case ONIGERR_MULTIPLEX_DEFINED_NAME:
    p = "multiplex defined name <%n>"; break;
  case ONIGERR_MULTIPLEX_DEFINITION_NAME_CALL:
    p = "multiplex definition name <%n> call"; break;
  case ONIGERR_NEVER_ENDING_RECURSION:
    p = "never ending recursion"; break;
  case ONIGERR_GROUP_NUMBER_OVER_FOR_CAPTURE_HISTORY:
    p = "group number is too big for capture history"; break;
  case ONIGERR_INVALID_CHAR_PROPERTY_NAME:
    p = "invalid character property name {%n}"; break;
  case ONIGERR_OVER_THREAD_PASS_LIMIT_COUNT:
    p = "over thread pass limit count"; break;

  default:
    p = "undefined error code"; break;
  }

  return p;
}


/* for ONIG_MAX_ERROR_MESSAGE_LEN */
#define MAX_ERROR_PAR_LEN   30

extern int
#ifdef HAVE_STDARG_PROTOTYPES
onig_error_code_to_str(UChar* s, int code, ...)
#else
onig_error_code_to_str(s, code, va_alist)
  UChar* s;
  int code;
  va_dcl 
#endif
{
  UChar *p, *q;
  OnigErrorInfo* einfo;
  int len;
  va_list vargs;

  va_init_list(vargs, code);

  switch (code) {
  case ONIGERR_UNDEFINED_NAME_REFERENCE:
  case ONIGERR_UNDEFINED_GROUP_REFERENCE:
  case ONIGERR_MULTIPLEX_DEFINED_NAME:
  case ONIGERR_MULTIPLEX_DEFINITION_NAME_CALL:
  case ONIGERR_INVALID_GROUP_NAME:
  case ONIGERR_INVALID_CHAR_IN_GROUP_NAME:
  case ONIGERR_INVALID_CHAR_PROPERTY_NAME:
    einfo = va_arg(vargs, OnigErrorInfo*);
    len = einfo->par_end - einfo->par;
    q = (UChar* )onig_error_code_to_format(code);
    p = s;
    while (*q != '\0') {
      if (*q == '%') {
	q++;
	if (*q == 'n') { /* '%n': name */
	  if (len > MAX_ERROR_PAR_LEN) {
	    xmemcpy(p, einfo->par, MAX_ERROR_PAR_LEN - 3);
	    p += (MAX_ERROR_PAR_LEN - 3);
	    xmemcpy(p, "...", 3);
	    p += 3;
	  }
	  else {
	    xmemcpy(p, einfo->par, len);
	    p += len;
	  }
	  q++;
	}
	else
	  goto normal_char;
      }
      else {
      normal_char:
	*p++ = *q++;
      }
    }
    *p = '\0';
    len = p - s;
    break;

  default:
    q = (UChar* )onig_error_code_to_format(code);
    len = strlen((char* )q);
    xmemcpy(s, q, len);
    s[len] = '\0';
    break;
  }

  va_end(vargs);
  return len;
}


void
#ifdef HAVE_STDARG_PROTOTYPES
onig_snprintf_with_pattern(char buf[], int bufsize, OnigEncoding enc,
			    char* pat, char* pat_end, char *fmt, ...)
#else
onig_snprintf_with_pattern(buf, bufsize, enc, pat, pat_end, fmt, va_alist)
    char buf[];
    int bufsize;
    OnigEncoding enc;
    char* pat;
    char* pat_end;
    const char *fmt;
    va_dcl
#endif
{
  int n, need, len;
  UChar *p, *s;
  va_list args;

  va_init_list(args, fmt);
  n = vsnprintf(buf, bufsize, fmt, args);
  va_end(args);

  need = (pat_end - pat) * 4 + 4;

  if (n + need < bufsize) {
    strcat(buf, ": /");
    s = (UChar* )(buf + strlen(buf));

    p = (UChar* )pat;
    while (p < (UChar* )pat_end) {
      if (*p == MC_ESC) {
	*s++ = *p++;
	len = enc_len(enc, *p);
	while (len-- > 0) *s++ = *p++;
      }
      else if (*p == '/') {
	*s++ = MC_ESC;
	*s++ = *p++;
      }
      else if (ONIGENC_IS_MBC_HEAD(enc, *p)) {
	len = enc_len(enc, *p);
	while (len-- > 0) *s++ = *p++;
      }
      else if (!ONIGENC_IS_CODE_PRINT(enc, *p) &&
	       !ONIGENC_IS_CODE_SPACE(enc, *p)) {
	char b[5];
	sprintf(b, "\\%03o", *p & 0377);
	len = strlen(b);
	while (len-- > 0) *s++ = *p++;
      }
      else {
	*s++ = *p++;
      }
    }

    *s++ = '/';
    *s   = '\0';
  }
}
