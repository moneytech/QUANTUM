// =============================================================================
// <xchar.h>
//
// Cross-platform character definitions.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_FDFBC95C31514A8999DAEAD813A8782C
#define H_FDFBC95C31514A8999DAEAD813A8782C

// -----------------------------------------------------------------------------

#define XCHAR(feat) (defined(XCHAR_##feat))

// -----------------------------------------------------------------------------

#if OS(WIN32)
  #include "windows/tchar.h"
#endif

// =============================================================================
// Constants
// -----------------------------------------------------------------------------

#if OS(WIN32)
  #define XEOF TEOF
#else
  #define XEOF EOF
#endif

// =============================================================================
// Types
// -----------------------------------------------------------------------------

#if OS(WIN32)
  typedef tchar_t xchar_t;
  typedef tschar_t xschar_t;
  typedef tuchar_t xuchar_t;
  typedef txchar_t xxchar_t;

  typedef tint_t xint_t;
#else
  typedef char xchar_t;
  typedef schar xschar_t;
  typedef uchar xuchar_t, xxchar_t;

  typedef int xint_t;
#endif

// =============================================================================
// Macros
// -----------------------------------------------------------------------------

#if OS(WIN32)
  #define X TEXT
  #define xmain tmain
#else
  #define X(x) (x)
  #define xmain main
#endif

// =============================================================================
// Functions
// -----------------------------------------------------------------------------

#if OS(WIN32)
  // <ctype.h>
  #define xisalnum istalnum
  #define xisalpha istalpha
  #define xisblank istblank
  #define xiscntrl istcntrl
  #define xisdigit istdigit
  #define xisgraph istgraph
  #define xislower istlower
  #define xisprint istprint
  #define xispunct istpunct
  #define xisspace istspace
  #define xisupper istupper
  #define xisxdigit istxdigit

  #define xtolower totlower
  #define xtoupper totupper

  // <inttypes.h>
  #define xstrtoimax tcstoimax
  #define xstrtoumax tcstoumax

  // <locale.h>
  #define xsetlocale tsetlocale

  // <stdio.h>
  #define xremove tremove
  #define xrename trename
  #define xtmpnam ttmpnam
  #define xtmpnam_r ttmpnam_s

  #define xfopen tfopen
  #define xfreopen tfreopen

  #define xfprintf ftprintf
  #define xfscanf ftscanf
  #define xprintf tprintf
  #define xscanf tscanf
  // Fixed version from <stdlib/windows/stdio.h>
  #define xsnprintf sntprintf
  #define xsprintf stprintf
  #define xsscanf stscanf
  #define xvfprintf vftprintf
  #define xvfscanf vftscanf
  #define xvprintf vtprintf
  #define xvscanf vtscanf
  // Fixed version from <stdlib/windows/stdio.h>
  #define xvsnprintf vsntprintf
  #define xvsprintf vstprintf
  #define xvsscanf vstscanf

  #define xfgetc fgettc
  #define xfgets fgetts
  #define xfputc fputtc
  #define xfputs fputts
  #define xgetc gettc
  #define xgetchar gettchar
  #define xgets getts
  #define xgets_s getts_s
  #define xputc puttc
  #define xputchar puttchar
  #define xputs putts
  #define xungetc ungettc

  #define xperror tperror

  // <stdlib.h>
  #define xatof ttof
  #define xatoi ttoi
  #define xatol ttol
  #define xatoll ttoi64
  #define xstrtod tcstod
  #define xstrtof tcstof
  #define xstrtol tcstol
  #define xstrtold tcstold
  #define xstrtoll tcstoi64
  #define xstrtoul tcstoul
  #define xstrtoull tcstoui64

  #define xgetenv tgetenv
  #define xsystem tsystem

  #define xitoa itot

  // <string.h>
  #define xstrcpy tcscpy
  #define xstrncpy tcsncpy
  #define xstrcat tcscat
  #define xstrncat tcsncat

  #define xstrcmp tcscmp
  #define xstrcasecmp tcsicmp
  #define xstrcoll tcscoll
  #define xstrncmp tcsncmp
  #define xstrncasecmp tcsnicmp
  #define xstrxfrm tcsxfrm

  #define xstrchr tcschr
  #define xstrcspn tcscspn
  #define xstrpbrk tcspbrk
  #define xstrrchr tcsrchr
  #define xstrspn tcsspn
  #define xstrstr tcsstr
  #define xstrtok tcstok
  #define xstrtok_r tcstok_s

  #define xstrerror tcserror
  #define xstrlen tcslen

  #define xstrdup tcsdup

  // <time.h>
  #define xasctime tasctime
  #define xasctime_r tasctime_s
  #define xctime tctime
  #define xctime_r tctime_s
  #define xstrftime tcsftime

  // Posix
  #define xaccess taccess
  #define xchdir tchdir
  #define xchmod tchmod
  #define xcreat tcreat
  #define xfdopen tfdopen
  #define xfullpath tfullpath
  #define xgetcwd tgetcwd
  #define xmkdir tmkdir
  #define xopen topen
  #define xpopen tpopen
  #define xrmdir trmdir
  #define xstat tstat
  #define xunlink tunlink
#else // OS(WIN32) ][
  // <ctype.h>
  #define xisalnum isalnum
  #define xisalpha isalpha
  #define xisblank isblank
  #define xiscntrl iscntrl
  #define xisdigit isdigit
  #define xisgraph isgraph
  #define xislower islower
  #define xisprint isprint
  #define xispunct ispunct
  #define xisspace isspace
  #define xisupper isupper
  #define xisxdigit isxdigit

  #define xtolower tolower
  #define xtoupper toupper

  // <inttypes.h>
  #define xstrtoimax strtoimax
  #define xstrtoumax strtoumax

  // <locale.h>
  #define xsetlocale setlocale

  // <stdio.h>
  #define xremove remove
  #define xrename rename
  #define xtmpnam tmpnam
  #define xtmpnam_r tmpnam_r

  #define xfopen fopen
  #define xfreopen freopen

  #define xfprintf fprintf
  #define xfscanf fscanf
  #define xprintf printf
  #define xscanf scanf
  #define xsnprintf snprintf
  #define xsprintf sprintf
  #define xsscanf sscanf
  #define xvfprintf vfprintf
  #define xvfscanf vfscanf
  #define xvprintf vprintf
  #define xvscanf vscanf
  #define xvsnprintf vsnprintf
  #define xvsprintf vsprintf
  #define xvsscanf vsscanf

  #define xfgetc fgetc
  #define xfgets fgets
  #define xfputc fputc
  #define xfputs fputs
  #define xgetc getc
  #define xgetchar getchar
  #define xgets gets
  #define xgets_s gets_s
  #define xputc putc
  #define xputchar putchar
  #define xputs puts
  #define xungetc ungetc

  #define xperror perror

  // <stdlib.h>
  #define xatof atof
  #define xatoi atoi
  #define xatol atol
  #define xatoll atoll
  #define xstrtod strtod
  #define xstrtof strtof
  #define xstrtol strtol
  #define xstrtold strtold
  #define xstrtoll strtoll
  #define xstrtoul strtoul
  #define xstrtoull strtoull

  #define xgetenv getenv
  #define xsystem system

  #define xitoa itoa

  // <string.h>
  #define xstrcpy strcpy
  #define xstrncpy strncpy
  #define xstrcat strcat
  #define xstrncat strncat

  #define xstrcmp strcmp
  #define xstrcasecmp strcasecmp
  #define xstrcoll strcoll
  #define xstrncmp strncmp
  #define xstrncasecmp strncasecmp
  #define xstrxfrm strxfrm

  #define xstrchr strchr
  #define xstrcspn strcspn
  #define xstrpbrk strpbrk
  #define xstrrchr strrchr
  #define xstrspn strspn
  #define xstrstr strstr
  #define xstrtok strtok
  #define xstrtok_r strtok_r

  #define xstrerror strerror
  #define xstrlen strlen

  #define xstrdup strdup

  // <time.h>
  #define xasctime asctime
  #define xasctime_r asctime_r
  #define xctime ctime
  #define xctime_r ctime_r
  #define xstrftime strftime

  // Posix
  #define xaccess access
  #define xchdir chdir
  #define xchmod chmod
  #define xcreat creat
  #define xfdopen fdopen
  #define xfullpath fullpath
  #define xgetcwd getcwd
  #define xmkdir mkdir
  #define xopen open
  #define xpopen popen
  #define xrmdir rmdir
  #define xstat stat
  #define xunlink unlink
#endif // !OS(WIN32)

// -----------------------------------------------------------------------------
// Convert between `xchar_t` and UTF-8 strings
// -----------------------------------------------------------------------------

#if OS(WIN32)
  #ifdef UNICODE
    #define XCHAR_UTF16
  #endif

  #define xstritoutf8 tcsitoutf8
  #define xstrtoutf8 tcstoutf8

  #define utf8toxstri utf8totcsi
  #define utf8toxstr utf8totcs
#else
  #define XCHAR_UTF8
#endif

// -----------------------------------------------------------------------------

#endif
