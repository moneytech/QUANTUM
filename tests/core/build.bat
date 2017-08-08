:: =============================================================================
:: QUANTUM test suite Windows build scripts.
::
:: Build the core test program.
::
:: Copyright Kristian Garnét.
:: -----------------------------------------------------------------------------

@echo off
cd /d "%~dp0"

:: Variables

set MARCH=-march=native
set QUANTUM=%CREATIVE%\QUANTUM

:: Create the build directory

if not exist build (
  mkdir build

  if %ERRORLEVEL% neq 0 (
    echo "Build error: couldn't create the build directory."
    exit /b %ERRORLEVEL%
  )
)

:: Compile the object files

gcc -O3 %MARCH% -c -I%QUANTUM% core.c -o build\core.o 2> build\core.log
if %ERRORLEVEL% neq 0 (echo "Build error: core.c" && exit /b %ERRORLEVEL%)

gcc -O0 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\assert.c -o build\assert.o 2> build\assert.log
if %ERRORLEVEL% neq 0 (echo "Build error: assert.c" && exit /b %ERRORLEVEL%)

:: Memory pool

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\memory\pool.c -o build\memory_pool.o 2> build\memory_pool.log
if %ERRORLEVEL% neq 0 (echo "Build error: memory\pool.c" && exit /b %ERRORLEVEL%)

:: String

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\string\buffer.c -o build\string_buffer.o 2> build\string_buffer.log
if %ERRORLEVEL% neq 0 (echo "Build error: string\buffer.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\string\search.c -o build\string_search.o 2> build\string_search.log
if %ERRORLEVEL% neq 0 (echo "Build error: string\search.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\string\replace.c -o build\string_replace.o 2> build\string_replace.log
if %ERRORLEVEL% neq 0 (echo "Build error: string\replace.c" && exit /b %ERRORLEVEL%)

:: Implicit string

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\string\implicit\buffer.c -o build\implicit_string_buffer.o 2> build\implicit_string_buffer.log
if %ERRORLEVEL% neq 0 (echo "Build error: string\implicit\buffer.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\string\implicit\search.c -o build\implicit_string_search.o 2> build\implicit_string_search.log
if %ERRORLEVEL% neq 0 (echo "Build error: string\implicit\search.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\string\implicit\replace.c -o build\implicit_string_replace.o 2> build\implicit_string_replace.log
if %ERRORLEVEL% neq 0 (echo "Build error: string\implicit\replace.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\string\implicit\compat.c -o build\implicit_string_compat.o 2> build\implicit_string_compat.log
if %ERRORLEVEL% neq 0 (echo "Build error: string\implicit\compat.c" && exit /b %ERRORLEVEL%)

:: Other

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\io.c -o build\io.o 2> build\io.log
if %ERRORLEVEL% neq 0 (echo "Build error: io.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\fs.c -o build\fs.o 2> build\fs.log
if %ERRORLEVEL% neq 0 (echo "Build error: fs.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\time.c -o build\time.o 2> build\time.log
if %ERRORLEVEL% neq 0 (echo "Build error: time.c" && exit /b %ERRORLEVEL%)

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\smp.c -o build\smp.o 2> build\smp.log
if %ERRORLEVEL% neq 0 (echo "Build error: smp.c" && exit /b %ERRORLEVEL%)

:: Windows only

gcc -O3 %MARCH% -c -I%QUANTUM% %QUANTUM%\quantum\windows\utils.c -o build\windows_utils.o 2> build\windows_utils.log
if %ERRORLEVEL% neq 0 (echo "Build error: windows\utils.c" && exit /b %ERRORLEVEL%)

:: Link the executable

gcc -mconsole ^
  build\core.o build\assert.o ^
  -o core.exe -lmingw32 -lmsvcr120
