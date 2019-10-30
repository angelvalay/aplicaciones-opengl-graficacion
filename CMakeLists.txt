cmake_minimum_required(VERSION 3.2)
project("practicas")

set(OpenGlLinkers -lGL -lglut -lGLEW -lm -lGLU -Wdeprecated -Wwrite-strings) # setting all the Glut libraries as one variable.

set(CMAKE_CXX_STANDARD 14)

add_executable(practicas-graficacion
#        src/practica_1/main.cpp)
#        src/proyecto_1/juego_1.cpp)
        src/practica_4/practica_4.cpp)
#        src/practica_rompecabezas.cpp)
#src/practica_pelotas.cpp)
target_link_libraries(practicas-graficacion ${OpenGlLinkers})