@echo off
SETLOCAL Enabledelayedexpansion
COLOR 0A
TITLE DEVHUB UNIFIED AUTOMATION SYSTEM

:: Target Workspace Directory
cd /d "C:\Users\shivb\OneDrive\Desktop\DSAA Interactive Dashboard"

:: Capture parameters from dashboard (e.g., %1 = "p1", %2 = "c", "cpp", "java", "py")
set FILENAME=%1
set LANG=%2

:: Guard Clause: If run manually without arguments, prompt the user
if "%FILENAME%"=="" (
    echo ===================================================
    echo    [SYSTEM ATTENTION] MANUAL OVERRIDE LAUNCHED
    echo ===================================================
    set /p FILENAME="Enter program prefix (e.g., p1, p2, ArrayControlInterface): "
)
if "%LANG%"=="" (
    echo Choose Runtime Environment: [ c ^| cpp ^| java ^| py ]
    set /p LANG="Enter language key: "
)

:: Convert language input to lowercase for uniform tracking
for %%L in (c cpp java py) do if /i "!LANG!"=="%%L" set LANG=%%L

echo ===================================================
echo   INITIALIZING TARGET DEPLOYMENT: !FILENAME!.!LANG!      
echo ===================================================
echo.

:: ===================================================
::   ROUTING ENGINE BASED ON SELECTED LANGUAGE
:: ===================================================

if "!LANG!"=="c" (
    COLOR 03
    TITLE TERMINAL EDGE CORE - C RUNTIME
    gcc !FILENAME!.c -o !FILENAME!_c_run.exe
    if !errorlevel! neq 0 goto COMPILER_ERROR
    echo [SUCCESS] Binary matrix loaded. Launching environment...
    echo. & echo --------------------------------------------------- & echo.
    !FILENAME!_c_run.exe
    if exist !FILENAME!_c_run.exe del !FILENAME!_c_run.exe
    goto SYSTEM_CLOSE
)

if "!LANG!"=="cpp" (
    COLOR 0D
    TITLE TERMINAL EDGE CORE - C++ RUNTIME
    g++ !FILENAME!.cpp -o !FILENAME!_cpp_run.exe
    if !errorlevel! neq 0 goto COMPILER_ERROR
    echo [SUCCESS] Binary compiled. Launching environment...
    echo. & echo --------------------------------------------------- & echo.
    !FILENAME!_cpp_run.exe
    if exist !FILENAME!_cpp_run.exe del !FILENAME!_cpp_run.exe
    goto SYSTEM_CLOSE
)

if "!LANG!"=="java" (
    COLOR 0B
    TITLE TERMINAL EDGE CORE - JAVA RUNTIME
    javac !FILENAME!.java
    if !errorlevel! neq 0 goto COMPILER_ERROR
    echo [SUCCESS] JVM Bytecode Ready. Initializing instance...
    echo. & echo --------------------------------------------------- & echo.
    java !FILENAME!
    goto SYSTEM_CLOSE
)

if "!LANG!"=="py" (
    COLOR 0E
    TITLE TERMINAL EDGE CORE - PYTHON RUNTIME
    echo [SUCCESS] Interpreter mapped. Booting script context...
    echo. & echo --------------------------------------------------- & echo.
    python !FILENAME!.py
    goto SYSTEM_CLOSE
)

:: If language string falls out of bounds
COLOR 0C
echo [CRITICAL ERROR] Environment '!LANG!' is not supported by core runtime.
goto SYSTEM_CLOSE

:COMPILER_ERROR
COLOR 0C
echo.
echo ---------------------------------------------------
echo   [CRITICAL] RUNTIME STRUCTURAL COMPILATION FAILED.
echo ---------------------------------------------------
pause
exit /b

:SYSTEM_CLOSE
echo.
echo ===================================================
echo    CORE TERMINATED. PRESS ANY KEY TO CONCLUDE MISSION.
echo ===================================================
pause > nul