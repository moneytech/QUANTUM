// =============================================================================
// <fs.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "build.h"
#include "core.h"

#if OS(WIN32)
  #include <Windows.h>
  #include "windows/tchar.h"
#endif

#include "fs.h"

// -----------------------------------------------------------------------------

#if !OS(WIN32)
static int fs_tree_remove_cb (const char_t* path, const stat_t* sb
, int flag, ftw_t* fb)
{
  switch (flag)
  {
    case FTW_D:
    case FTW_DNR:
    case FTW_DP: return rmdir (path);
    default: return unlink (path);
  }

  return 0;
}
#endif // !OS(WIN32)

bint fs_tree_remove (const char_t* path)
{
#if OS(WIN32)
  tchar_t wpath[4096];

  size_t sz = utf8totcsi (path, wpath, numof (wpath));
  if (unlikely (sz == 0)) return false;

  SHFILEOPSTRUCT op =
  {
    NULL,
    FO_DELETE,
    wpath,
    NULL,
    FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT | FOF_NO_UI,
    FALSE,
    NULL,
    NULL
  };

  return SHFileOperation (&op) ? false : true;
#else
  return nftw (path, fs_tree_remove_cb, 8u, FTW_DEPTH | FTW_PHYS);
#endif
}
