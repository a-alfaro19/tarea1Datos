# tarea1Datos

Este proyecto consta de dos herramientas de línea de comandos diseñadas para trabajar con archivos binarios grandes que contienen números enteros aleatorios:

## `generator`

`generator` es una herramienta para crear archivos binarios grandes llenos de números enteros aleatorios. Puedes especificar el tamaño del archivo y la ruta de salida donde se guardarán los datos generados.

## `sorter`

`sorter` es una herramienta para ordenar archivos binarios grandes que contienen números enteros. Esta herramienta permite ordenar los datos en el archivo binario de entrada utilizando diferentes algoritmos de ordenamiento y guardar el resultado en un archivo de salida.

## Requisitos

Asegúrate de tener instalados los siguientes programas:

- [CMake](https://cmake.org/download/)
- Un compilador compatible con C++ (como `g++` en Linux, `clang` en macOS, o `MSVC` en Windows)
- [Git](https://git-scm.com/) (si necesitas clonar el repositorio)

## Clonar el Repositorio

Si aún no has clonado el repositorio, usa el siguiente comando:

```sh
git clone https://github.com/a-alfaro19/tarea1Datos.git
cd tarea1Datos
```

## Construcción

1. **Crea un directorio de construcción**:
```sh
mkdir build
cd build
```

2. **Configura el proyecto con CMake**:
```sh
cmake ..
```

3. **Construye el proyecto**:
```sh
make
```

## Ejecución

Para ejecutar el programa generator, usa el siguiente comando:
```sh
./generator --size <SIZE> --output <OUTPUT FILE PATH>
```

Donde:
- <SIZE> es el tamaño del archivo binario en términos de número de enteros.
- <OUTPUT FILE PATH> es la ruta del archivo de salida donde se guardarán los datos generados.

Para ejecutar el programa sorter, usa el siguiente comando:
```sh
./sorter --input <INPUT FILE PATH> --output <OUTPUT FILE PATH> --alg <ALGORITHM>
```

Donde:
- <INPUT FILE PATH> es la ruta del archivo binario de entrada que deseas ordenar.
- <OUTPUT FILE PATH> es la ruta del archivo de salida donde se guardarán los datos ordenados.
- <ALGORITHM> es el algoritmo de ordenamiento que se utilizará (quick, bubble, insertion).

## Nota

La construcción y ejecución debe hacer en el directorio del programa a utilizar.
