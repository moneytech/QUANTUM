// =============================================================================
// <windows/utils.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "../build.h"

#include <Windows.h>

#include "../core.h"
#include "../wide.h"
#include "tchar.h"

#include "utils.h"

// -----------------------------------------------------------------------------

int win_args_get (tchar_t*** argv)
{
#ifdef UNICODE

  int argc;

  tchar_t* cmd = GetCommandLineW();

  if (cmd == null)
  {
    *argv = null;
    return 0;
  }

  // Get rid of leading whitespace as per remarks:
  // https://msdn.microsoft.com/en-us/library/windows/desktop/bb776391(v=vs.85).aspx
  while (chr_is_wspace_zero (*cmd)) cmd++;

  *argv = CommandLineToArgvW (cmd, &argc);

  return (*argv == null) ? 0 : argc;

#else

  *argv = __argv;
  return __argc;

#endif
}

// -----------------------------------------------------------------------------

bint win_console (bint rstdin, bint inherit)
{
  if (!inherit)
  {
    // Detach from the parent console
    FreeConsole();

    // Create the new console window
    if (!AllocConsole()) return false;

    goto attach;
  }

  // Create the console window
  if (AllocConsole())
  {
attach:
    // Attach to it
    AttachConsole (GetCurrentProcessId());

    // Redirect the standard output to the newly created console
    freopen ("CONOUT$", "w", stdout);

    // Do the same with the standard input
    if (rstdin) freopen ("CONIN$", "r", stdin);
  }

  return true;
}
