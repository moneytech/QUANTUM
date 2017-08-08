// =============================================================================
// <core/language/keywords/storage.h>
//
// Storage class keywords.
//
// Copyright Kristian Garnét.
// -----------------------------------------------------------------------------

#ifndef H_E1C534433F9F4CDF9F348FAFC946C350
#define H_E1C534433F9F4CDF9F348FAFC946C350

// -----------------------------------------------------------------------------
// `thread`: variable declaration with the thread-local storage (TLS) duration
#if HAVE(C11) && HAVE(C_THREADS)
  #define thread _Thread_local
#elif C(GNU)
  #define thread __thread
#elif (С_MSC_VER >= 1310)
  // Visual Studio 2003 .NET and later provide the `thread` specifier
  #define thread __declspec(thread)
#endif

// -----------------------------------------------------------------------------

#endif
