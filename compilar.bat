@echo off
g++ -std=c++17 -O2 -Wall -static -o simulador.exe src\*.cpp
if errorlevel 1 (
    echo.
    echo No compilo. Revisa los errores de arriba.
    exit /b 1
)
echo Listo: simulador.exe
