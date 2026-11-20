# Simulador de memoria y procesos

Proyecto final de Sistemas Operativos del equipo 5. Ingeniería en Sistemas Computacionales, Universidad Autónoma de Aguascalientes.

Simulador en consola hecho en C++. Coloca los procesos en memoria con Primer Ajuste o con Buddy System y los atiende con Round Robin.

## Integrantes

- Guillermo: Primer Ajuste e integración
- Germán: menú y generador de procesos
- Leonardo: Buddy System
- Héctor: ciclo y Round Robin

## Compilar y ejecutar

Se necesita g++ (WinLibs). En Windows:

```
.\compilar.bat
.\simulador.exe
```

En Linux:

```
g++ -std=c++17 -O2 -Wall -o simulador src/*.cpp
./simulador
```

Las pruebas van en la carpeta pruebas, cada una con su propio main().

## Ramas

Cada integrante trabaja en su rama: primer-ajuste, buddy, ciclo-rr y menu. Cada parte se integra a main con un pull request.
