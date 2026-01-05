@echo off
setlocal enabledelayedexpansion

:: ------------------------------
:: C++ Auto Finder & Runner
:: ------------------------------

echo Checking for C++ compiler (g++)...

g++ --version >nul 2>&1
if not %errorlevel%==0 (
    echo g++ not found.
    echo Please install MinGW or MSYS2 and add g++ to PATH.
    pause
    exit /b
)

echo g++ is installed.
echo.

:: Get current directory (where bat is)
set WORK_DIR=%~dp0
cd /d "%WORK_DIR%"

echo Searching for C++ files in:
echo %WORK_DIR%
echo.

:: Find cpp files
set count=0
for %%f in (*.cpp) do (
    set /a count+=1
    set file[!count!]=%%f
    echo !count! - %%f
)

if %count%==0 (
    echo No .cpp files found!
    pause
    exit /b
)

echo.
set /p choice=Enter file number to compile and run: 

if not defined file[%choice%] (
    echo Invalid selection!
    pause
    exit /b
)

set CPP_FILE=!file[%choice%]!
set OUTPUT_FILE=%~n0_output.exe

echo.
echo Compiling "!CPP_FILE!" ...
g++ "!CPP_FILE!" -o "!OUTPUT_FILE!"

if %errorlevel%==0 (
    echo Compilation successful!
    echo Running program...
    echo.
    "!OUTPUT_FILE!"
) else (
    echo Compilation failed!
)

pause