@echo off
setlocal
for %%I in (.) do set "SCRIPT_DIR=%%~fI"
if not "%CD%"=="%SCRIPT_DIR%" (
    echo [31mYou must run this script from its parent directory![0m
    exit /b 1
)
echo [34mBuilding PghServer...[0m
cmake -S . -B build
if errorlevel 1 exit /b 1
cmake --build build
if errorlevel 1 exit /b 1
echo [34mBuilt PghServer![0m
endlocal