// =============================================================================
// <fs.h>
//
// File system routines.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E6DD520A5CDA4A729F894C0140EE7C11
#define H_E6DD520A5CDA4A729F894C0140EE7C11

// -----------------------------------------------------------------------------

#if OS(WIN32)
  #include "stdlib/stdlib.h"
#endif

#include <sys/types.h>
#include <sys/stat.h>

#if !OS(WIN32)
  #include <sys/statvfs.h>
#endif

#include <fcntl.h>

#if OS(WIN32)
  #include <io.h>
  #include <direct.h>

  #include "windows/posix.h"
#else
  #include <fnmatch.h>
  #include <ftw.h>

  #include <dirent.h>

  #include <unistd.h>
#endif

// =============================================================================
// Types
// -----------------------------------------------------------------------------
// `stat()` structure
// -----------------------------------------------------------------------------

#if OS(WIN32)
  typedef struct __stat64 stat_t;
#else
  typedef struct stat stat_t;
#endif

#if !OS(WIN32)
  typedef struct FTW ftw_t;
#endif

typedef stat_t fs_stat_t;

// =============================================================================
// Functions
// -----------------------------------------------------------------------------
// Fully resolve the provided `path` to its absolute representation
// in the host's file system
static inline bint fs_path_abs (const char_t* path, char_t* buf, size_t bufsz)
{
#if OS(WIN32)
  return (fullpath (buf, path, bufsz) != null);
#else
  // `buf` must be at least of `PATH_MAX` size
  if (unlikely (bufsz < PATH_MAX))
  {
    errno = ERANGE;
    return false;
  }

  return (realpath (path, buf) != null);
#endif
}

// -----------------------------------------------------------------------------
// Remove the entire directory tree
bint fs_tree_remove (const char_t* path);

// -----------------------------------------------------------------------------

#endif
