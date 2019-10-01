# aplicaciones-opengl-graficacion
Ejercicios y practicas en C++ y Python para el desarrollo de aplicaciones graficas con la libreria de OpenGL.

Instalacion de OpenGL en Linux (C/C++/Python)

En una terminal de sistema (LINUX), con CONEXION A INTERNET, teclean los siguientes comandos. Verificar que el comando anterior haya finalizado
con exito para pasar al siguiente.

```
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install glew-utils
sudo apt-get install libglew-dev
sudo apt-get install mesa-utils
sudo apt-get install freeglut3
sudo apt-get install freeglut3-dev
```

```
// Librerias para reproduccion de Sonido
sudo apt-get install libopenal-dev
sudo apt-get install libalut-dev
```
Comando para ver que version de OpenGL se tiene
```
glxinfo | grep "OpenGL version"
```
Librerias de Python:
```
python -V
sudo apt-get install python3-pip
sudo apt-get install python3-opengl
sudo -H pip3 install numpy
sudo -H pip3 install matplotlib
```
Latex (descarga casi 2 GB, se puede interrumpir y reanudar mas tarde sin perder avance):
```
sudo apt-get install texlive-full
```