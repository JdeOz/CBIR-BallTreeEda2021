# CBIR-BallTreeEda2021

Proyecto final del curso de Estructuras de Datos Avanzadas UCSP CCOMP6-1 2021.

## Requisitos:

1. Este programa solo corre en Linux o en windows con un WSL ya que usa un sistemas de pipes exclusivo de Linux para la comunicación entre C++ y Python.

    * Instalar  WSL Ubunto para windows aqui: https://www.microsoft.com/store/productId/9N9TNGVNDL3Q

2. Versión mínima de Python "3.6".

3. Versión mínima de C++ "11".

    *Instalar compilador c++ para ubuntu: `$ sudo apt install g++`

4. Para compilar el código de C++ se utilizará CMake (versión mínima 3.10).

   *Instalar compilador Cmake para ubuntu: `$ sudo apt install cmake`

5. Para ejecutar el código de Python se utilizará Poetry (versión mínima 1.1.12).

   *Instalar compilador Poetry para ubuntu:<br/>
`$ curl -sSL https://raw.githubusercontent.com/python-poetry/poetry/master/get-poetry.py | python -`<br/>
o `$ curl -sSL https://raw.githubusercontent.com/python-poetry/poetry/master/get-poetry.py | python3 -`

## Instrucciones de compilación y ejecución

Pasos:

### a. Compilar con Cmake

1. Entrar a la carpeta "BallTree_CPP" y abrir un terminal desde ahí.

2. Con los siguientes comandos crearemos un carpeta llamada "build" y entraremos en ella:<br/>

   * `$ mkdir build`<br/>
   * `$ cd build`

3. Dentro de la carpeta "build" ejecuta los comandos:<br/>

   * `$ cmake ..`<br/>
   * `$ make`<br/>
   
**Esto generará 2 ejecutables (*GenerateBallTree* y *BallTreeInterface*) dentro de la carpeta "Interfaz_PythonFlask".**

5. Ahora tenemos que abrir la carpeta "Interfaz_PythonFlask" y ejecutar el archivo "GenerateBallTree" de la siguente forma:<br/>

  * `$ ./GenerateBallTree`<br/>
  
**Esto generará el Ball Tree, imprimirá el tiempo que demoró y al final lo guardará en en el archivo "BallTreeFile.bin" dentro de la carpeta "Files".**

6. No tenemos que ejecutarlo manualmente el archivo "BallTreeInterface", pero tenemos que cerciorarnos que tenga permisos de ejecución.

### b. Ejecutar la interfaz Gráfica

1. Entrar a la carpeta "Interfaz_PythonFlask" y abrir un terminal desde ahí.

2. Instalaremos las dependencias del proyecto y crear un venv con Poetry usando el siguiente comando:<br/>

   * `$ poetry install`<br/>
   
3. Ejecutaremos el proyecto con Poetry usando alguno de los siguientes comandos:<br/>

   * `$ poetry run python3 app.py ` o `$ poetry run python app.py `

4. Si no hubo ningún problema la consola nos mostrará la dirección donde se esta ejecutando nuestra interfaz, tenemos que abrirla con algún navegador. Tambien nos imprimirá en el terminal el tiempo de indexación y el tiempo que demora el KNN cada vez que hacemos una búsqueda.<br/>

**Estos tiempos se meclarán entre la información que suele imprimir flask en el terminal.**

## Interfaz Gráfica:

Esta interfaz consta de 3 partes:

1. Una pizarra donde podemos dibujar un número para hacer la consulta al Ball Tree.
2. Un formulario para subur una imagen para hacer la consulta al Ball Tree.
3. Aqui aparecen las respuestas listadas en orden de semejanza y la etiqueta de cada imagen es su id correspondiente.


## Contenido:

El repositorio consta de 2 carpetas: "BallTree_CPP" e "Interfaz_PythonFlask".

### 1. BallTree_CPP

* En esta carpeta tenemos el "CMakeLists.txt" y la carpeta "src" con todos los archivos necesarios para su correcta compilación.
* En "src" tenemos 2 archivos main, el primero se llama "GenerateBallTree.cpp" y el segundo "BallTreeInterface.cpp".
* Tenemos que compilar nuestros archivos con CMake; al hacerlo se generarán dentro de la carpeta "Interfaz_PythonFlask" 2 ejecutables:

    #### a. GenerateBallTree

    Lo que hace el "GenerateBallTree" al ejecutarlo manualmente es crear el árbol desde 0, imprimir en el terminal lo que se demoró en generarlo y al final escribe el árbol ya generado en un archivo llamado "BallTreeFile.bin" dentro de la carpeta "Interfaz_PythonFlask/File".
    
    #### b. BallTreeInterface

    Este es el programa que usa la interfaz para hacerle consultas al árbol, lo que hace es leer el árbol desde "BallTreeFile.bin" (este proceso lo hace mucho más rápido que si lo generamos desde 0), luego entra en un bucle infinito esperando a que la interfaz le haga consultas. Python se encarga de ejecutarlo asi que no tenemos que ejecutarlo manualmente.

### 2. Interfaz_PythonFlask

* En esta carpeta se encunetran todos los archivos necesarios para ejecutar la interfaz gráfica en Python - Flask (app.py, functions.py, static y templates).
* Tambien se crearán aqui los ejecutables que compilaremos en Cmake.
* En la carpeta Files guardaremos el dataset de MNIST y el "BallTreeFile.bin",
* Para el manejo de las dependencias utilizamos la herramienta Poetry, este descargará las librerias necesarias y ejecutará el archivo principal "app.py".



