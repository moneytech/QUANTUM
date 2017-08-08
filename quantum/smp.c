// =============================================================================
// <smp.c>
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include "build.h"

#if OS(BSD) || OS(MACOS)
  #include <sys/types.h>
  #include <sys/sysctl.h>
#elif OS(LINUX)
  #include <unistd.h>
#elif OS(WIN32)
  #include <Windows.h>
#endif

#include "core.h"
#include "smp.h"

// -----------------------------------------------------------------------------

uint smp_core_count (void)
{
#if OS(BSD) || OS(MACOS)
  int cores;
  int mib[4];

  size_t len = sizeof (cores);
  mib[0] = CTL_HW;

  #ifdef HW_AVAILCPU
    mib[1] = HW_AVAILCPU;
    if (sysctl (mib, 2u, &cores, &len, null, 0) != 0)
  #else
    mib[1] = HW_NCPU;
    if (sysctl (mib, 2u, &cores, &len, null, 0) != 0)
  #endif
    {
      return 1u;
    }

#elif OS(LINUX)
  long cores = sysconf (_SC_NPROCESSORS_ONLN);

#elif OS(WIN32)
  SYSTEM_INFO sysinfo;

  GetSystemInfo (&sysinfo);
  DWORD cores = sysinfo.dwNumberOfProcessors;

#elif SMP(OPENMP)
  int cores = omp_get_num_procs();

#else
  uint cores = 0;
#endif

  return ((cores > 0) ? (uint)cores : 1u);
}
