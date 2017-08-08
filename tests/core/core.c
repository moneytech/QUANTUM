// =============================================================================
// QUANTUM test suite.
//
// Core test program.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#include <quantum/build.h>
#include <quantum/core.h>

#if OS(WIN32)
  #include <Windows.h>
#endif

#include <quantum/net.h>
#include <quantum/hash.h>
#include <quantum/wide.h>
#include <quantum/xchar.h>

// -----------------------------------------------------------------------------

int main (int argc, char** argv)
{
  quantum_assertions();

  return EXIT_SUCCESS;
}
