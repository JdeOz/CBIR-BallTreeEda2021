# CBIR-BallTreeEda2021
Proyecto final del curso de Estructuras de Datos Avanzadas UCSP CCOMP6-1 2021.

## Requisitos:
1. Este programa solo corre en Linux o en un WLS ya que usa un sistemas de pipe para la
comunicación entre C++ y Python exclusivo de linux.
2. Versión mínima de Python 3.6.
3. Versión mínima de C++ 11.
4. Para compilar el codigo de C++ se utilizará CMake (versión mínima 3.10).
5. Para Ejecutar el codigo de Python se utilizará Poetry (versión mínima 1.1.12).

## Instrucciones
Pasos:
### a. Compilar con Cmake
1. Entrar a la carpeta "BallTree_CPP" y abrir un terminal desde ahí.
2. Crear un carpeta llamada "build" luego entrar en ella.<br/>
  1. `$ mkdir build`<br/>
  2. `$ cd build`
3. Dentro de la carpeta "build" ejecuta los comandos:<br/>
  1. `$ cmake ..`<br/>
  2. `$ make`<br/>
     **Esto generará 2 ejecutables dentro de la carpeta "Interfaz_PythonFlask".**
4. Ahora tenemos que abrir la carpeta "Interfaz_PythonFlask" y ejecutar el archivo
   "GenerateBallTree" de la siguente forma:<br/>
  1. `$ ./GenerateBallTree`<br/>
     **Esto generara el Ball Tree, luego imprimirá el tiempo que demoro y al final lo guardará
     en en el archivo "BallTreeFile.bin" dentro de la carpeta "Files".**
5. El archivo "BallTreeInterface" no tenemos que ejecutarlo manualmente, pero tenemos
   que cerciorarnos que tenga permisos de ejecución.

### b. Ejecutar la interfaz Gráfica
1. Entrar a la carpeta "Interfaz_PythonFlask" y abrir un terminal desde ahí.
2. Instalar las dependencias de del proyecto de poetry con el siguiente comando:<br/>
   `$ poetry install`<br/>
3. Ejecutar el proyecto en poetry con el siguiente comando:<br/>
   `$ poetry run python3 app.py ` o `$ poetry run python app.py `

## Contenido:
El repositorio consta de 2 carpetas: "BallTree_CPP" e "Interfaz_PythonFlask".

### 1. BallTree_CPP
* En esta carpeta tenemos el "CMakeLists.txt" y la carpeta "src" con todos los archivos
necesarios para su correcta compilación.
* En "src" tenemos 2 archivos main, el primero se llama "GenerateBallTree.cpp" y
el segundo "BallTreeInterface.cpp".
* Tenemos que compilar nuestros archivos con CMake, al hacerlo se generarán
dentro de la carpeta "Interfaz_PythonFlask" 2 ejecutables:

    #### a. GenerateBallTree
    Lo que hace el "GenerateBallTree" al ejecutarlo manualmente (./GenerateBallTree) es
    crear el árbol desde 0, imprimir en el terminal
    lo que se demoró en generarlo y al final escribe el árbol ya generado en un
    archivo llamado "BallTreeFile.bin" dentro de la carpeta "Interfaz_PythonFlask/File".
    #### b. BallTreeInterface
    Este es el programa que usa la interfaz para hacerle consultas al árbol, lo que
    hace es leer el árbol desde "BallTreeFile.bin" (este proceso lo hace mucho más
    rápido si lo generamos desde 0), luego entra en un bucle infinito esperando a que
    la interfaz le haga consultas. (No tenemos que ejecutarlo manualmante).

### 2. Interfaz_PythonFlask
* En esta carpeta se encunetran todos los archivos necesarios para ejecutar la interfaz
gráfica en flask.
* Para el manejo del las dependencias utilizamos la herramienta Poetry, este descargará
las librerias necesarias y ejecutará el archivo principal "app.py".



