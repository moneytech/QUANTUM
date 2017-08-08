:: =============================================================================
:: QUANTUM test suite Windows build scripts.
::
:: Clean up the build environment.
::
:: Copyright Kristian Garnét.
:: -----------------------------------------------------------------------------

@echo off
cd /d "%~dp0"

:: Remove build directories
for /d %%d in (*) do (
  rem Uncomment to remove the built executables as well
  rem del "%%d\*.exe"

  if exist "%%d\build" (
    del "%%d\build\*.o"
    del "%%d\build\*.log"

    rmdir "%%d\build"
  )
)
