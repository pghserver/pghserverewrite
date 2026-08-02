@echo off
setlocal
call build.bat
if errorlevel 1 exit /b 1
if exist build\PghServer.exe (
    build\PghServer.exe %*
) else if exist build\Debug\PghServer.exe (
    build\Debug\PghServer.exe %*
) else if exist build\Release\PghServer.exe (
    build\Release\PghServer.exe %*
) else (
    echo Could not find PghServer executable! I mean, it's your fault for using Microslop's barely-even-software.
    exit /b 1
)
endlocal